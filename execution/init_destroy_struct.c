/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:10:13 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/02 10:50:46 by vdelafos         ###   ########.fr       */
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
	cmd_struct->cmd_path_lst = ft_find_path(minishell->envp);
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

t_mini	*ft_init_mini(char *envp[])
{
	t_mini	*minishell;

	minishell = malloc(sizeof(*minishell));
	ft_check_malloc(minishell);
	minishell->nb_cmd = -1;
	minishell->envp = envp;
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
