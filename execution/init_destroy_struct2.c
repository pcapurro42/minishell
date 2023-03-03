/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_struct2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:21:15 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/03 18:38:40 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_destroy_mini_tools(t_mini_tools *mini_tools)
{
	free(mini_tools->pwd);
	free(mini_tools->old_pwd);
	pls_free(mini_tools->envp);
	free(mini_tools);
}