/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:10:13 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/04 16:48:40 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_init_cmd(t_mini *minishell)
{
	t_cmd	*cmd_struct;

	cmd_struct = malloc(sizeof(*cmd_struct));
	ft_check_malloc(cmd_struct);
	cmd_struct->infile_fd = -1;
	cmd_struct->outfile_fd = -1;
	cmd_struct->cmd_path_lst = ft_find_path(minishell->mini_tools->envp);
	cmd_struct->cmd_arg = NULL;
	return (cmd_struct);
}

void	ft_destroy_cmd(t_cmd *cmd_struct)
{
	if (cmd_struct)
	{
		if (cmd_struct->cmd_path_lst)
			pls_free(cmd_struct->cmd_path_lst);
		if (cmd_struct->cmd_arg)
			pls_free(cmd_struct->cmd_arg);
		free(cmd_struct);
	}
}

t_mini	*ft_init_mini(t_mini_tools *mini_tools)
{
	t_mini	*minishell;

	minishell = malloc(sizeof(*minishell));
	ft_check_malloc(minishell);
	minishell->nb_cmd = -1;
	minishell->mini_tools = mini_tools;
	minishell->cmd_lst = NULL;
	return (minishell);
}

void	ft_destroy_mini(t_mini *minishell)
{
	int	i;

	if (minishell)
	{
		if (minishell->cmd_lst)
		{
			i = 0;
			while ((minishell->cmd_lst)[i])
			{
				pls_free((minishell->cmd_lst)[i]);
				i++;
			}
			free(minishell->cmd_lst);
		}
	}
}

t_mini_tools	*ft_init_mini_tools(char *envp[])
{
	mini_tools = malloc(sizeof(*mini_tools));
	mini_tools->envp = ft_cpy_envp(envp);
	mini_tools->pwd = ft_get_pwd(mini_tools->envp);
	mini_tools->old_pwd = ft_strdup(mini_tools->pwd);
	mini_tools->g_last_return_code = 0;
	mini_tools->input = 0;
	return (mini_tools);
}
