/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:30:54 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/13 23:32:45 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;

	if (s == NULL)
		return ((char *) s);
	if (ft_strlen(s) <= start)
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	new_s = ft_calloc(len + 1, sizeof(*new_s));
	if ((new_s == NULL) || (len == 0))
		return (new_s);
	ft_strlcpy(new_s, &(s[start]), len + 1);
	return (new_s);
}
