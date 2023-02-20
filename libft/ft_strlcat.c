/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:33:16 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/12 17:14:31 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	len = ft_strlen(src) + ft_strlen(dst);
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (dst[j] != '\0')
		j++;
	while ((j < dstsize - 1) && (src[i] != '\0'))
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (len);
}
