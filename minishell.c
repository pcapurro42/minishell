/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/07 17:22:39 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_name(void)
{
	char	*name;
	int		address;

	address = (int)&name * (-1);
	while (address > 10)
		address = address / 10;
	if (address % 2 == 0)
	{
		name = ft_strdup("miniquoi:~$ ");
		printf("______  _______       ____________             _____    \n");
		printf("___   |/  /__(_)_________(_)_  __ \\___  __________(_)  \n");
		printf("__  /|_/ /__  /__  __ \\_  /_  / / /  / / /  __ \\_  /  \n");
		printf("_  /  / / _  / _  / / /  / / /_/ // /_/ // /_/ // /    \n");
		printf("/_/  /_/  /_/  /_/ /_//_/  \\___\\_\\_____/ \\____//_/   \n\n");
		ft_check_malloc(name);
	}
	else
	{
		name = ft_strdup("minifeur:~$ ");
		printf("______  _______       _____________                   \n");
		printf("___   |/  /__(_)_________(_)__  __/________  _________\n");
		printf("__  /|_/ /__  /__  __ \\_  /__  /_ _  _ \\  / / /_  ___/\n");
		printf("_  /  / / _  / _  / / /  / _  __/ /  __/ /_/ /_  /    \n");
		printf("/_/  /_/  /_/  /_/ /_//_/  /_/    \\___/\\____/ /_/     \n\n");
		ft_check_malloc(name);
	}
	return (name);
}

static void	ft_clean_stdin(void)
{
	struct termios idk;

	tcgetattr(STDIN_FILENO, &idk);							// = récupère la config du terminal
	idk.c_lflag &= ~ECHOCTL;									// = efface le flag 'ECHO' dans idk.c_lflag
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &idk);				// = applique la config modifiée
}

// tcgetattr = fonction permettant de récupérer la config du terminal
// tcsetattr = fonction permettant d'appliquer la config mise en argument

// '&=' : opérateur binaire combinant && et =
// '~' : opérateur binaire de négation (= inverse chaque bit de ECHO)

void	ft_handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		if (g_pid != -1)
		{
			kill(g_pid, SIGKILL);
			ft_putstr_fd("", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	main(int argc, char **argv, char *envp[])
{
	char			*name;
	char			*input;
	t_mini			*minishell;
	t_mini_tools	*mini_tools;

	(void) argc;
	name = ft_get_name();
	mini_tools = ft_init_mini_tools(envp, argv);
	input = NULL;
	g_pid = -1;
	ft_clean_stdin();
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_signal);
	while (6)
	{
		g_pid = -1;
		minishell = ft_init_mini(mini_tools);
		if (input)
			free(input);
		input = readline(name);
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		add_history(input);
		if (input[0] != '\0')
			ft_analyze_input(input, minishell);
	}
	return (0);
}
