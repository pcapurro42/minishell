/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:40:11 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/06 12:08:37 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_to_cmd_arg2(t_cmd *cmd_struct, t_nb *nb)
{
	char	**temp;

	if (!cmd_struct->cmd_arg)
	{
		cmd_struct->cmd_arg = malloc(\
			sizeof(*cmd_struct->cmd_arg) * (nb->nb_to_add + 1));
		ft_check_malloc(cmd_struct->cmd_arg);
	}
	else
	{
		temp = malloc(sizeof(*temp) * \
			(nb->nb_to_add + nb->len_cmd_arg + 1));
		ft_check_malloc(temp);
		nb->len_cmd_arg = 0;
		while (cmd_struct->cmd_arg[nb->len_cmd_arg])
		{
			temp[nb->len_cmd_arg] = cmd_struct->cmd_arg[nb->len_cmd_arg];
			nb->len_cmd_arg++;
		}
		free(cmd_struct->cmd_arg);
		cmd_struct->cmd_arg = temp;
		cmd_struct->cmd_arg[nb->len_cmd_arg] = NULL;
	}
}

void	ft_add_to_cmd_arg(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	nb->nb_to_add = 0;
	while (minishell->cmd_lst[i][nb->j + nb->nb_to_add] && \
	ft_strncmp(minishell->cmd_lst[i][nb->j + nb->nb_to_add], "<", 2) != 0 && \
	ft_strncmp(minishell->cmd_lst[i][nb->j + nb->nb_to_add], ">", 2) != 0 && \
	ft_strncmp(minishell->cmd_lst[i][nb->j + nb->nb_to_add], "<<", 3) != 0 && \
	ft_strncmp(minishell->cmd_lst[i][nb->j + nb->nb_to_add], ">>", 3) != 0)
		nb->nb_to_add++;
	ft_add_to_cmd_arg2(cmd_struct, nb);
	nb->id_str_to_add = 0;
	while (nb->id_str_to_add < nb->nb_to_add)
	{
		cmd_struct->cmd_arg[nb->len_cmd_arg] = minishell->cmd_lst[i][nb->j];
		nb->j++;
		nb->len_cmd_arg++;
		nb->id_str_to_add++;
	}
	cmd_struct->cmd_arg[nb->len_cmd_arg] = NULL;
}

int	ft_check_chevron(t_mini *minishell, t_cmd *cmd_struct, int i, t_nb *nb)
{
	nb->j = 0;
	nb->len_cmd_arg = 0;
	while (minishell->cmd_lst[i][nb->j])
	{
		if (ft_strncmp(minishell->cmd_lst[i][nb->j], "<", 2) == 0)
			ft_case_left_chevron(minishell, cmd_struct, i, nb);
		else if (ft_strncmp(minishell->cmd_lst[i][nb->j], ">", 2) == 0)
			ft_case_right_chevron(minishell, cmd_struct, i, nb);
		else if (ft_strncmp(minishell->cmd_lst[i][nb->j], "<<", 3) == 0)
			ft_case_dbleft_chevron(minishell, cmd_struct, i, nb);
		else if (ft_strncmp(minishell->cmd_lst[i][nb->j], ">>", 3) == 0)
			ft_case_dright_chevron(minishell, cmd_struct, i, nb);
		else
			ft_add_to_cmd_arg(minishell, cmd_struct, i, nb);
		if (cmd_struct->infile_fd == -2 || cmd_struct->outfile_fd == -2)
		{
			free(nb);
			return (1);
		}
	}
	return (0);
}
