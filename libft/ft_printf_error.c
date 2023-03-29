/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:00:27 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/13 08:00:28 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_str(va_list ap)
{
	int		i;
	char	*temp;

	i = 0;
	temp = va_arg(ap, char *);
	if (!temp)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (temp[i] != '\0')
	{
		write(2, &temp[i], 1);
		i++;
	}
	return (i);
}

static int	ft_print_char(va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	write(1, &c, 1);
	return (1);
}

static int	ft_get_conv(char x, va_list ap)
{
	if (x == 's')
		return (ft_print_str(ap));
	if (x == 'c')
		return (ft_print_char(ap));
	return (0);
}

int	ft_printf_error(const char *str, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	va_start(ap, str);
	while ((size_t)i < ft_strlen((char *)str))
	{
		if (str[i] != '%')
		{
			write(2, &str[i], 1);
			len++;
		}
		else
		{
			len = len + ft_get_conv(str[i + 1], ap);
			i++;
		}
		i++;
	}
	va_end(ap);
	return (len);
}
