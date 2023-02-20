/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 03:01:54 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/15 04:06:13 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*point_lst;
	t_list	*new_lst;

	if ((lst == NULL) || (f == NULL) || (del == NULL))
		return (NULL);
	new_lst = ft_lstnew(f((*lst).content));
	if (new_lst == NULL)
		return (NULL);
	point_lst = new_lst;
	lst = (*lst).next;
	while (lst != NULL)
	{
		(*point_lst).next = ft_lstnew(f((*lst).content));
		if ((*point_lst).next == NULL)
		{
			ft_lstclear(&point_lst, del);
			return (NULL);
		}
		point_lst = (*point_lst).next;
		lst = (*lst).next;
	}
	return (new_lst);
}
