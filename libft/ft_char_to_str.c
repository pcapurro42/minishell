/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:35:32 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/27 16:35:32 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	ft_check_malloc(str);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
