/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:04 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/20 11:38:31 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_name(void)
{
	int		address;
	char	*name;

	address = (int)&name * (-1);
	while (address > 10)
		address = address / 10;
	if (address % 2 == 0)
	{
		printf("______  _______       _____________                   \n");
		printf("___   |/  /__(_)_________(_)__  __/________  _________\n");
		printf("__  /|_/ /__  /__  __ \\_  /__  /_ _  _ \\  / / /_  ___/\n");
		printf("_  /  / / _  / _  / / /  / _  __/ /  __/ /_/ /_  /    \n");
		printf("/_/  /_/  /_/  /_/ /_//_/  /_/    \\___/\\____/ /_/     \n\n");
		name = ft_strdup("minifeur:~$ ");
	}
	else
	{
		printf("______  _______       ____________             _____    \n");
		printf("___   |/  /__(_)_________(_)_  __ \\___  __________(_)  \n");
		printf("__  /|_/ /__  /__  __ \\_  /_  / / /  / / /  __ \\_  /  \n");
		printf("_  /  / / _  / _  / / /  / / /_/ // /_/ // /_/ // /    \n");
		printf("/_/  /_/  /_/  /_/ /_//_/  \\___\\_\\_____/ \\____//_/   \n\n");
		name = ft_strdup("miniquoi:~$ ");
	}
	return (name);
}

int	main(void)
{
	char	*name;
	char	*input;

	name = ft_get_name();
	input = NULL;
	g_last_return_code = 0;
	while (6)
	{
		if (input)
			free(input);
		input = NULL;
		while (input == NULL)
			input = readline(name);
		if (input[0] != '\0')
			ft_analyze_input(input);
	}
	return (0);
}
