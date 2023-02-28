/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_replacer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:51:24 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/28 16:51:25 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_replace_if_necessary(char *input, t_mini *minishell)
{
	int		i;
	char	*str;

	i = 0;
	while (input[i] != '\0')
	{
		i++;
	}
	minishell = NULL;
	str = NULL;
	return (input);
}

char	**ft_check_variables(char **str, t_mini *minishell)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$') != NULL)
			str[i] = ft_replace_if_necessary(str[i], minishell);
		i++;
	}
	return (str);
}