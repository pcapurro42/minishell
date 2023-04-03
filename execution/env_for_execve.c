/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:33:22 by vdelafos          #+#    #+#             */
/*   Updated: 2023/04/03 14:47:10 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_fail(t_cmd	*cmd_struct, t_mini *minishell, int i)
{
	if (ft_strlen(cmd_struct->cmd_arg[0]) == 0 || \
	(ft_strlen(cmd_struct->cmd_arg[0]) == 1 && \
	cmd_struct->cmd_arg[0][0] == '.') || \
	(ft_strlen(cmd_struct->cmd_arg[0]) == 2 && \
	cmd_struct->cmd_arg[0][0] == '.' && \
	cmd_struct->cmd_arg[0][1] == '.'))
		ft_cmd_error(cmd_struct->cmd_arg[0]);
	ft_error_msg(minishell->cmd_lst[0][i]);
}

static int	ft_find_nb_complete_env(char **envp)
{
	int		envp_len;
	int		i;

	envp_len = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			envp_len++;
		i++;
	}
	return (envp_len);
}

char	**ft_envp_without_export(char **envp)
{
	int		envp_len;
	int		i;
	int		j;
	char	**envp_cpy;

	envp_len = ft_find_nb_complete_env(envp);
	envp_cpy = malloc(sizeof(*envp_cpy) * (envp_len + 1));
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			envp_cpy[j] = envp[i];
			j++;
		}
		i++;
	}
	envp_cpy[j] = NULL;
	return (envp_cpy);
}
