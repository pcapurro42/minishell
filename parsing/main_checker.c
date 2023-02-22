/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:05:44 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/22 06:11:51 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_commands(char **str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (0);
}

char	*ft_analyze_input(char *input)
{
	int		i;
	char	*temp;
	char	**str;

	i = 0;
	temp = ft_clean_input(input);
	if (ft_syntax_checker(temp) != 0)
		return (free(temp), NULL);
	else
		str = ft_split(temp, ' ');
	ft_check_commands(str);
	return (NULL);
}

// "|"
// ">"
// ">>"
