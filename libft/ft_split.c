/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 23:42:51 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/14 17:49:37 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c_in_s(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	if (s[i] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if ((s[i] == c) && (s[i + 1] != c) && (s[i + 1] != '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	count_char_to_c(char const *s, char c)
{
	int	i;

	i = 0;
	while ((s[i] != c) && (s[i] != '\0'))
		i++;
	return (i);
}

static char	**ft_nul_case(char const *s)
{
	char	**tab;

	if (ft_strlen(s) == 0)
	{
		tab = malloc(sizeof(*tab));
		if (tab == NULL)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	tab = malloc(2 * sizeof(*tab));
	if (tab == NULL)
		return (NULL);
	tab[0] = malloc((ft_strlen(s) + 1) * sizeof(**tab));
	ft_strlcpy(tab[0], s, count_char_to_c(s, '\0') + 1);
	if (tab[0] == NULL)
	{
		free(tab);
		return (NULL);
	}
	tab[1] = NULL;
	return (tab);
}

static char	**ft_main_split(char const *s, char c, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < count_c_in_s(s, c))
	{
		while (s[j] == c)
			j++;
		tab[i] = malloc((count_char_to_c(&(s[j]), c) + 1) * sizeof(**tab));
		if (tab[i] == NULL)
		{
			while (i >= 0)
				free(tab[i--]);
			free(tab);
			return (NULL);
		}
		ft_strlcpy(tab[i], &(s[j]), count_char_to_c(&(s[j]), c) + 1);
		j += count_char_to_c(&(s[j]), c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (c == '\0')
		return (ft_nul_case(s));
	tab = malloc((count_c_in_s(s, c) + 1) * sizeof(*tab));
	if (tab == NULL)
		return (NULL);
	tab = ft_main_split(s, c, tab);
	if (tab == NULL)
		return (NULL);
	return (tab);
}
