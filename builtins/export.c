/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:42 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/03 19:00:27 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_builtins(char **cmd_arg, t_mini *minishell)
{
	char	**new_envp;
	int		envp_len;
	int		nb_export;

	nb_export = 0;
	while (cmd_arg[1 + nb_export])
		nb_export++;
	if (nb_export == 0)
		return(ft_env_builtins(minishell->mini_tools->envp));
	if (minishell->mini_tools->envp == NULL)
	{
		minishell->mini_tools->envp = \
		malloc(sizeof(*minishell->mini_tools->envp));
		minishell->mini_tools->envp[0] = NULL;
	}
	envp_len = 0;
	while (minishell->mini_tools->envp[envp_len])
		envp_len++;
	new_envp = malloc(sizeof(*new_envp) * (envp_len + 1 + nb_export));
	envp_len = 0;
	while (minishell->mini_tools->envp[envp_len])
	{
		new_envp[envp_len] = minishell->mini_tools->envp[envp_len]; 
		envp_len++;
	}
	nb_export = 0;
	while (cmd_arg[1 + nb_export])
	{
		new_envp[envp_len + nb_export] = cmd_arg[nb_export + 1];
		nb_export++;
	}
	new_envp[envp_len + nb_export] = NULL;
	free(minishell->mini_tools->envp);
	minishell->mini_tools->envp = new_envp;
	return ;
}

// modif variable