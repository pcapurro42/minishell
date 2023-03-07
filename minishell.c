/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/07 11:08:28 by vdelafos         ###   ########.fr       */
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
	struct termios backup;

	tcgetattr(STDIN_FILENO, &backup);						// = sauvegarde la config initiale du terminal (avant de la modifier)

	tcgetattr(STDIN_FILENO, &idk);							// = récupère la config du terminal
	idk.c_lflag &= ~ECHO;									// = efface le flag 'ECHO' dans idk.c_lflag
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &idk);				// = applique la config modifiée

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &backup);			// = restaure la config originale
}

// tcgetattr = fonction permettant de récupérer la config du terminal
// tcsetattr = fonction permettant d'appliquer la config mise en argument

// '&=' : opérateur binaire combinant && et =
// '~' : opérateur binaire de négation (= inverse chaque bit de ECHO)

void	ft_handle_signal(int signal)
{
	ft_clean_stdin();
	if (signal == SIGINT)
	{
		if (global_pid != -1)
		{
			kill(global_pid, SIGKILL);
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

// tcsetattr
// tcgetattr
// tgetent

int	main(int argc, char **argv, char *envp[])
{
	char			*name;
	char			*input;
	t_mini			*minishell;
	t_mini_tools	*mini_tools;

	(void) argc;
	(void) argv;
	name = ft_get_name();
	mini_tools = ft_init_mini_tools(envp);
	input = NULL;
	global_pid = -1;
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_signal);
	while (6)
	{
		global_pid = -1;
		minishell = ft_init_mini(mini_tools);
		if (input)
			free(input);
		input = readline(name);
		if (input == NULL)
		{
			global_pid = -2;
			exit(0);
		}
		add_history(input);
		if (input[0] != '\0')
			ft_analyze_input(input, minishell);
	}
	return (0);
}
