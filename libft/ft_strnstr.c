/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 02:37:09 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/15 02:37:10 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *) haystack);
	if (len == 0)
		return (NULL);
	while ((haystack[i] != '\0') && (i < len))
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && ((i + j) < len))
		{
			j++;
			if (needle[j] == '\0')
				return ((char *) &(haystack[i]));
		}
		i++;
	}
	return (NULL);
}
