/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:17:33 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/12 17:14:55 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_char;
	const char	*src_char;
	size_t		i;

	dst_char = dst;
	src_char = src;
	i = 0;
	if ((dst == NULL) && (src == NULL))
		return (dst);
	while (i < n)
	{
		dst_char[i] = src_char[i];
		i++;
	}
	return (dst);
}
