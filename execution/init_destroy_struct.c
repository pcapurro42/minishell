/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:10:13 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/23 08:55:04 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	*ft_init_mini(char *envp[])
{
	t_mini	*minishell;

	minishell = malloc(sizeof(*minishell));
	ft_check_malloc(minishell);
	minishell->nb_cmd = -1;
	minishell->infile_mod = -1;
	minishell->outfile_mod = -1;
	minishell->infile_fd = -1;
	minishell->outfile_fd = -1;
	minishell->infile = NULL;
	minishell->outfile = NULL;
	minishell->limiter = NULL;
	minishell->envp = envp;
	minishell->cmd_path_lst = ft_find_path(envp);
	minishell->cmd_lst = NULL;
	return (minishell);
}

void	ft_destroy_mini(t_mini *minishell)
{
	int i;

	if (minishell)
	{
		if (minishell->cmd_path_lst)
			pls_free(minishell->cmd_path_lst);
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
		free(minishell->infile);
		free(minishell->outfile);
		free(minishell);
	}
}