/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:11:30 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/11 18:38:03 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (((dst == NULL) && (src == NULL)) || (n == 0))
		return (dst);
	if (dst > src)
	{
		i = n - 1;
		while (i > 0)
		{
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
			i--;
		}
		((unsigned char *) dst)[0] = ((unsigned char *) src)[0];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
			i++;
		}
	}
	return (dst);
}
