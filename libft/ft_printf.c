/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:05:35 by vdelafos          #+#    #+#             */
/*   Updated: 2022/12/11 17:16:15 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_len(unsigned long long int nb, const char conv)
{
	int	len;

	len = 0;
	if (nb == 0)
		len += ft_putstr_len("0x0");
	else
	{
		len += ft_putstr_len("0x");
		len += ft_puthexalong_len(nb, conv);
	}
	return (len);
}

int	ft_putx_len(unsigned int nb, const char conv)
{
	int	len;

	len = 0;
	if (nb == 0)
		len += ft_putchar_len('0');
	else
		len += ft_puthexa_len(nb, conv);
	return (len);
}

int	ft_putall_len(const char conv, va_list argptr)
{
	int	len;

	len = 0;
	if (conv == 'c')
		len += ft_putchar_len(va_arg(argptr, int));
	else if (conv == 's')
		len += ft_putstr_len(va_arg(argptr, char *));
	else if (conv == 'p')
		len += ft_putptr_len(va_arg(argptr, unsigned long long int), 'x');
	else if ((conv == 'd') || (conv == 'i'))
		len += ft_putnbr_len(va_arg(argptr, int));
	else if (conv == 'u')
		len += ft_putnbru_len(va_arg(argptr, unsigned int));
	else if ((conv == 'x') || (conv == 'X'))
		len += ft_putx_len(va_arg(argptr, unsigned int), conv);
	else if (conv == '%')
		len += ft_putchar_len('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list		argptr;
	int			len;

	len = 0;
	if (format == NULL)
		return (0);
	va_start(argptr, format);
	while (*format != '\0')
	{
		if (*format != '%')
		{
			len += ft_putchar_len(*format);
			format++;
		}
		else
		{
			len += ft_putall_len(format[1], argptr);
			format += 2;
		}
	}
	va_end(argptr);
	return (len);
}
