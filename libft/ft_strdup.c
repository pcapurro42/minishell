/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:29:27 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/07 15:58:09 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	s2 = malloc((ft_strlen(s1) + 1) * sizeof(*s1));
	ft_check_malloc(s2);
	ft_strlcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}
