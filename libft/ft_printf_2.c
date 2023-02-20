/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:17:08 by vdelafos          #+#    #+#             */
/*   Updated: 2022/12/11 17:16:27 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_writenbr_len(int n)
{
	int	len;

	if (n != 0)
	{
		len = ft_writenbr_len(n / 10);
		if (n > 0)
			ft_putchar_len((n % 10) + 48);
		if (n < 0)
			ft_putchar_len((-1 * (n % 10)) + 48);
		return (len + 1);
	}
	return (0);
}

int	ft_putnbr_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += ft_putchar_len('0');
	if (n < 0)
		len += ft_putchar_len('-');
	if (n != 0)
		len += ft_writenbr_len(n);
	return (len);
}

int	ft_writenbru_len(unsigned int n)
{
	int	len;

	if (n != 0)
	{
		len = ft_writenbru_len(n / 10);
		ft_putchar_len((n % 10) + 48);
		return (len + 1);
	}
	return (0);
}

int	ft_putnbru_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += ft_putchar_len('0');
	if (n != 0)
		len += ft_writenbru_len(n);
	return (len);
}
