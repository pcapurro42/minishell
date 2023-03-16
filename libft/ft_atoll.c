/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:59:52 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/16 23:04:59 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoll(const char *str)
{
	long long int	nb;
	int				is_pos;

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
