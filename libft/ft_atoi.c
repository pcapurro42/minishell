/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:14:24 by vdelafos          #+#    #+#             */
/*   Updated: 2023/01/27 14:19:58 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	is_pos;

	nb = 0;
	is_pos = 1;
	while ((*str == 32) || ((9 <= *str) && (*str <= 13)))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			is_pos = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nb += ((int) *str) - 48;
		if (ft_isdigit(str[1]))
			nb *= 10;
		str++;
	}
	return (nb * is_pos);
}
