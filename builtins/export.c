/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:42 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/09 19:27:41 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_no_arg_builtins(char **envp)
{
	int i;
	
	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(envp[i], '='))
		{
			write(1, envp[i], ft_strchr_i(envp[i], '=') + 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(&(envp[i][ft_strchr_i(envp[i], '=') + 1]), 1);
			ft_putchar_fd('\"', 1);
		}
		else
			ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return ;
}

void	ft_export_builtins(char **cmd_arg, t_mini *minishell)
{
	char	**new_envp;
	int		envp_len;
	int		nb_export;

	nb_export = 0;
	while (cmd_arg[nb_export + 1])
		nb_export++;
	if (nb_export == 0)
		return(ft_export_no_arg_builtins(minishell->mini_tools->envp));
	envp_len = 0;
	while (minishell->mini_tools->envp[envp_len])
		envp_len++;
	new_envp = malloc(sizeof(*new_envp) * (envp_len + nb_export + 1));
	envp_len = 0;
	while (minishell->mini_tools->envp[envp_len])
	{
		new_envp[envp_len] = minishell->mini_tools->envp[envp_len]; 
		envp_len++;
	}
	nb_export = 0;
	while (cmd_arg[nb_export + 1])
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