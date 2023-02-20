/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:10:56 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/15 16:19:55 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	i;

	i = 0;
	if ((count != 0) && ((SIZE_MAX / count) < size))
		return (NULL);
	memory = malloc(count * size);
	if (memory == NULL)
		return (NULL);
	while (i < (size * count))
	{
		((char *) memory)[i] = '\0';
		i++;
	}
	return (memory);
}
