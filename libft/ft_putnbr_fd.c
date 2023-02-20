/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:38:23 by vdelafos          #+#    #+#             */
/*   Updated: 2023/01/30 16:52:28 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_nb(int n, int fd)
{
	if (n != 0)
	{
		ft_write_nb(n / 10, fd);
		if (n > 0)
			ft_putchar_fd((n % 10) + 48, fd);
		if (n < 0)
			ft_putchar_fd((-1 * (n % 10)) + 48, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n != 0)
		ft_write_nb(n, fd);
}
