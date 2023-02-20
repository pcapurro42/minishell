/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:29:49 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/15 16:29:51 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char) s1[i] == (unsigned char) s2[i]) && (i < n - 1) && \
		(s1[i] != '\0') && (s2[i] != '\0'))
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
