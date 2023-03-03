/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:38:28 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/02 12:43:06 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_case_left_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	if (cmd_struct->infile_fd >= 0)
		close(cmd_struct->infile_fd);
	cmd_struct->infile_fd = open(minishell->cmd_lst[i][nb->j + 1], \
		O_RDONLY);
	if (cmd_struct->infile_fd < 0)
		file_not_open(cmd_struct, minishell->cmd_lst[i][nb->j + 1]);
	nb->j += 2;
}

static void	ft_case_right_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	if (cmd_struct->outfile_fd >= 0)
		close(cmd_struct->outfile_fd);
	cmd_struct->outfile_fd = open(minishell->cmd_lst[i][nb->j + 1], \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd_struct->outfile_fd < 0)
		perror(minishell->cmd_lst[i][nb->j + 1]);
	nb->j += 2;
}

static void	ft_case_dbleft_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	if (cmd_struct->infile_fd >= 0)
		close(cmd_struct->infile_fd);
	ft_here_doc(cmd_struct, \
		minishell->cmd_lst[i][nb->j + 1]);
	nb->j += 2;
}

static void	ft_case_dright_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	if (cmd_struct->outfile_fd >= 0)
		close(cmd_struct->outfile_fd);
	cmd_struct->outfile_fd = open(minishell->cmd_lst[i][nb->j + 1], \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	if (cmd_struct->outfile_fd < 0)
		perror(minishell->cmd_lst[i][nb->j + 1]);
	nb->j += 2;
}

void	ft_build_struct_cmd(t_mini *minishell, t_cmd *cmd_struct, int i)
{
	t_nb	*nb;

	nb = malloc(sizeof(*nb));
	if (!nb)
		ft_error();
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
	}
	// ft_remove_quotes(cmd_struct->cmd_arg);
	if (cmd_struct->infile_fd < 0)
		cmd_struct->infile_fd = -1;
	if (cmd_struct->outfile_fd < 0)
		cmd_struct->outfile_fd = -1;
}
