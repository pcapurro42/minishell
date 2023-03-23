/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:33:56 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/15 16:25:28 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_start(char const *s1, char const *set)
{
	int	start;
	int	i;
	int	in_set;

	start = 0;
	in_set = 1;
	while ((s1[start] != '\0') && (in_set == 1))
	{
		i = 0;
		in_set = 0;
		while (set[i] != '\0')
		{
			if (s1[start] == set[i])
				in_set = 1;
			i++;
		}
		if (in_set == 1)
			start++;
	}
	return (start);
}

static int	ft_find_end(char const *s1, char const *set)
{
	int	end;
	int	i;
	int	in_set;

	end = ft_strlen(s1) - 1;
	in_set = 1;
	while ((end >= 0) && (in_set))
	{
		i = 0;
		in_set = 0;
		while (set[i] != '\0')
		{
			if (s1[end] == set[i])
				in_set = 1;
			i++;
		}
		if (in_set == 1)
			end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*s2;

	if ((s1 == NULL) || (set == NULL))
		return (NULL);
	start = ft_find_start(s1, set);
	end = ft_find_end(s1, set);
	len = end - start;
	if (len <= 0)
	{
		len = 0;
		s2 = malloc(len * sizeof(*s2) + 1);
	}
	else
		s2 = malloc(len * sizeof(*s2) + 2);
	ft_check_malloc(s2);
	ft_strlcpy(s2, &(s1[start]), len + 2);
	return (s2);
}
