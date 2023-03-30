/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lower_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:04:39 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/30 10:52:35 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lower_input(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(*new_str) * (ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		if (str[i] >= 65 && str[i] <= 90)
			new_str[i] = str[i] + 32;
		else
			new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
