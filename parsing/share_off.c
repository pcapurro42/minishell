/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triple_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:01:45 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/27 18:01:47 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_get_pipe_number(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

char	***ft_share_off(char **str)
{
	int		i;
	int		j;
	int		k;
	char	***fstr;

	i = 0;
	j = 0;
	k = 0;
	fstr = malloc(sizeof(char **) * (ft_get_pipe_number(str) + 1) + 1);
	return (NULL);
}

// cat Makefile >> test.txt