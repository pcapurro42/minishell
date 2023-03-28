/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/28 19:43:51 by vdelafos         ###   ########.fr       */
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
	}
	else
	{
		name = ft_strdup("minifeur:~$ ");
		printf("______  _______       _____________                   \n");
		printf("___   |/  /__(_)_________(_)__  __/________  _________\n");
		printf("__  /|_/ /__  /__  __ \\_  /__  /_ _  _ \\  / / /_  ___/\n");
		printf("_  /  / / _  / _  / / /  / _  __/ /  __/ /_/ /_  /    \n");
		printf("/_/  /_/  /_/  /_/ /_//_/  /_/    \\___/\\____/ /_/     \n\n");
	}
	return (name);
}

void	ft_init_minishell(void)
{
	struct termios	idk;

	tcgetattr(STDIN_FILENO, &idk);
	idk.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &idk);
	g_global = malloc(sizeof(*g_global));
	ft_check_malloc(g_global);
	g_global->g_pid = -2147483648;
	g_global->g_last_return_code = 0;
}

void	ft_print_shell(int number)
{
	if (number != 0)
	{
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

void	ft_handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		if (g_global->g_pid != -2147483648)
		{
			if (g_global->g_pid < 0)
			{
				g_global->g_pid = g_global->g_pid * (-1);
				g_global->g_last_return_code = -1;
			}
			else
			{
				ft_putstr_fd("^C\n", 1);
				g_global->g_last_return_code = -130;
			}
			kill(g_global->g_pid, SIGKILL);
			ft_print_shell(1);
		}
		else
		{
			ft_print_shell(0);
			g_global->g_last_return_code = 1;
		}
	}
	else
		rl_redisplay();
}

int	main(int argc, char **argv, char *envp[])
{
	char			*name;
	char			*input;
	t_mini			*minishell;
	t_mini_tools	*mini_tools;

	(void) argc;
	input = NULL;
	name = ft_get_name();
	mini_tools = ft_init_mini_tools(envp, argv);
	ft_init_minishell();
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_signal);
	while ((((6 * 6 == 36) != 4) != 0))
	{
		minishell = ft_init_mini(mini_tools);
		input = readline(name);
		if (input == NULL)
			ft_destroy_mini(minishell, input);
		if (input[0] != '\0')
			ft_analyze_input(input, minishell);
		ft_destroy_mini(minishell, input);
		free(input);
	}
	return (0);
}
