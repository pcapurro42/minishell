/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:36:51 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/13 04:22:21 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_builtins(char **envp)
{
	int i;
	
	if (envp == NULL)
		return (0);
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
	return (0);
}