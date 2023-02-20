/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 00:47:50 by vdelafos          #+#    #+#             */
/*   Updated: 2022/11/15 01:34:38 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_last;

	if ((lst == NULL) || (new == NULL))
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_last = ft_lstlast(*lst);
	(*lst_last).next = new;
}
