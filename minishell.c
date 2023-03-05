/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/04 18:10:12 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_minifeur(void)
{
	printf("______  _______       _____________                   \n");
	printf("___   |/  /__(_)_________(_)__  __/________  _________\n");
	printf("__  /|_/ /__  /__  __ \\_  /__  /_ _  _ \\  / / /_  ___/\n");
	printf("_  /  / / _  / _  / / /  / _  __/ /  __/ /_/ /_  /    \n");
	printf("/_/  /_/  /_/  /_/ /_//_/  /_/    \\___/\\____/ /_/     \n\n");
}

static void	ft_print_miniquoi(void)
{
	printf("______  _______       ____________             _____    \n");
	printf("___   |/  /__(_)_________(_)_  __ \\___  __________(_)  \n");
	printf("__  /|_/ /__  /__  __ \\_  /_  / / /  / / /  __ \\_  /  \n");
	printf("_  /  / / _  / _  / / /  / / /_/ // /_/ // /_/ // /    \n");
	printf("/_/  /_/  /_/  /_/ /_//_/  \\___\\_\\_____/ \\____//_/   \n\n");
}

char	*ft_get_name(void)
{
	int		address;
	char	*name;

	address = (int)&name * (-1);
	while (address > 10)
		address = address / 10;
	if (address % 2 == 0)
	{
		ft_print_minifeur();
		name = ft_strdup("minifeur:~$ ");
		ft_check_malloc(name);
	}
	else
	{
		ft_print_miniquoi();
		name = ft_strdup("miniquoi:~$ ");
		ft_check_malloc(name);
	}
	return (name);
}

void	ft_handle_signal(int signal)
{
	if (signal == SIGINT)
		;
}

int	main(int argc, char **argv, char *envp[])
{
	char			*name;
	t_mini			*minishell;
	t_mini_tools	*mini_tools;

	(void) argc;
	(void) argv;
	name = ft_get_name();
	mini_tools = ft_init_mini_tools(envp);
	input = NULL;
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_signal);
	while (6)
	{
		minishell = ft_init_mini(mini_tools);
		if (input)
			free(input);
		input = readline(name);
		add_history(input);
		if (input[0] != '\0')
			ft_analyze_input(input, minishell);
	}
	return (0);
}
