/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 08:14:46 by vdelafos          #+#    #+#             */
/*   Updated: 2022/12/16 09:10:01 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\0')
		i++;
	while (i != 0)
	{
		if (s[i] == (char) c)
			return (i);
		i--;
	}
	if (s[i] == (char) c)
		return (i);
	return (-1);
}
