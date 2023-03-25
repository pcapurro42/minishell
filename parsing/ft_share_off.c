/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_share_off.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 02:30:44 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/25 02:30:45 by pcapurro         ###   ########.fr       */
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

static char	***ft_allocate_strs(char ***fstr, char **str, int size)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	fstr[size] = NULL;
	while (i != size)
	{
		while (str[j] != NULL && str[j][0] != '|')
		{
			j++;
			k++;
		}
		fstr[i] = malloc(sizeof(char *) * (k) + 1);
		ft_check_malloc(fstr[i]);
		fstr[i][k] = NULL;
		if (str[j] == NULL)
			return (fstr);
		j++;
		i++;
		k = 0;
	}
	return (fstr);
}

char	***ft_share_off(char **str)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	***fstr;

	i = 0;
	j = 0;
	k = 0;
	size = ft_get_pipe_number(str) + 1;
	fstr = malloc(sizeof(char **) * (size) + 1);
	ft_check_malloc(fstr);
	fstr = ft_allocate_strs(fstr, str, size);
	while (fstr[i] != NULL)
	{
		while (str[j] != NULL && str[j][0] != '|')
			fstr[i][k++] = ft_strdup(str[j++]);
		j++;
		i++;
		k = 0;
	}
	return (fstr);
}
