/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:36:51 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/08 20:04:02 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_builtins(char **envp)
{
	int i;
	
	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return ;
}