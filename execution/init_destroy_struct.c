/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:10:13 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/22 13:34:51 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	ft_init_mini(char **envp)
{
	t_mini	*minishell;

	minishell = malloc(sizeof(*minishell));
	minishell->append_mod = 0;
	minishell->infile = -1;
	minishell->outfile = -1;
	minishell->envp = envp;
	minishell->cmd_lst = NULL;
	minishell->history = NULL;
	minishell->cmd_path_lst = ft_find_path(envp);
}