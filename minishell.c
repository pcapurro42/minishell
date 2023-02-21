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

// char	*ft_analyze_input(char *input);

int	main(void)
{
	char	*input;

	input = NULL;
	while (6)
	{
		if (input)
			free(input);
		input = NULL;
		while (input == NULL)
			input = readline("minifeur:~$ ");
		// ft_analyze_input(input);
	}
	return (1);
}
