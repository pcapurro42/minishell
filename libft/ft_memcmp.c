/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:15:53 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/11 17:30:48 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*str1;
	const unsigned char		*str2;

	str1 = s1;
	str2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((str1[i] == str2[i]) && (i < n - 1))
		i++;
	return (str1[i] - str2[i]);
}
