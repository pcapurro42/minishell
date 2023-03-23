/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:41:06 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/14 17:49:49 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenint(int n)
{
	int	lenint;

	lenint = 0;
	if (n <= 0)
		lenint++;
	while (n != 0)
	{
		n /= 10;
		lenint++;
	}
	return (lenint);
}

char	*ft_itoa(int n)
{
	char	*ans;
	int		i;

	i = ft_lenint(n) - 1;
	ans = malloc(ft_lenint(n) * sizeof(*ans) + 1);
	ft_check_malloc(ans);
	ans[i + 1] = '\0';
	if (n == 0)
		ans[i] = '0';
	if (n < 0)
		ans[0] = '-';
	while (n != 0)
	{
		if (n > 0)
			ans[i] = ((n % 10) + 48);
		else
			ans[i] = ((-1 * (n % 10)) + 48);
		n /= 10;
		i--;
	}
	return (ans);
}
