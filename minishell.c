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

void	ft_clean_stdin(void)
{
	struct termios idk;

	tcgetattr(STDIN_FILENO, &idk);
	idk.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &idk);
}

// '&=' : opérateur binaire combinant && et =
// '~' : opérateur binaire de négation (= inverse chaque bit de ECHO)

void	ft_handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		if (g_global->g_pid != -2147483648)
		{
			if (g_global->g_pid < 0)
			{
				g_global->g_pid = g_global->g_pid * (-1);
				g_global->g_last_return_code = 1;
			}
			else
			{
				ft_putstr_fd("^C\n", 1);
				g_global->g_last_return_code = 130;
			}
			kill(g_global->g_pid, SIGKILL);
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
			g_global->g_last_return_code = 1;
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
	g_global = malloc(sizeof(*g_global));
	ft_check_malloc(g_global);
	g_global->g_pid = -2147483648;
	g_global->g_last_return_code = 0;
	name = ft_get_name();
	mini_tools = ft_init_mini_tools(envp, argv);
	input = NULL;
	ft_clean_stdin();
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_signal);
	while (6)
	{
		g_global->g_pid = -2147483648;
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
			if (ft_analyze_input(input, minishell) == 1)
				g_global->g_last_return_code = 258;
	}
	return (0);
}
