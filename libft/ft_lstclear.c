/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:54:08 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/15 03:36:17 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_main_lstclear(t_list **lst, void (*del)(void*))
{
	if (*lst == NULL)
		return ;
	if ((**lst).next != NULL)
		ft_lstclear((&(**lst).next), del);
	ft_lstdelone(*lst, del);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	ft_main_lstclear(lst, del);
	*lst = NULL;
}
