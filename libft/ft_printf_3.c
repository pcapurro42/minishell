/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:02:22 by vdelafos          #+#    #+#             */
/*   Updated: 2022/12/11 17:16:53 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_len(unsigned char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_len(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		len += ft_putstr_len("(null)");
	else
	{
		while (str[len] != '\0')
			len += ft_putchar_len(str[len]);
	}
	return (len);
}

int	ft_puthexa_len(unsigned int nb, const char conv)
{
	int	len;

	if (nb == 0)
		return (0);
	else
	{
		len = ft_puthexa_len(nb / 16, conv);
		if ((nb % 16) <= 9)
			ft_putchar_len((nb % 16) + 48);
		else if (conv == 'x')
			ft_putchar_len(87 + (nb % 16));
		else
			ft_putchar_len(55 + (nb % 16));
		return (len + 1);
	}
}

int	ft_puthexalong_len(unsigned long long int nb, const char conv)
{
	int	len;

	if (nb == 0)
		return (0);
	else
	{
		len = ft_puthexalong_len(nb / 16, conv);
		if ((nb % 16) <= 9)
			ft_putchar_len((nb % 16) + 48);
		else if (conv == 'x')
			ft_putchar_len(87 + (nb % 16));
		else
			ft_putchar_len(55 + (nb % 16));
		return (len + 1);
	}
}
