/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:38:28 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/29 12:46:24 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_case_left_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	char	*infile;

	infile = ft_substitute_str(minishell->cmd_lst[i][nb->j + 1]);
	if (cmd_struct->infile_fd >= 0)
		close(cmd_struct->infile_fd);
	cmd_struct->infile_fd = open(infile, O_RDONLY);
	if (cmd_struct->infile_fd < 0)
	{
		ft_msg(infile);
		cmd_struct->infile_fd = -2;
		g_global->g_last_return_code = 1;
	}
	free(infile);
	nb->j += 2;
}

void	ft_case_right_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	char	*outfile;

	outfile = ft_substitute_str(minishell->cmd_lst[i][nb->j + 1]);
	if (cmd_struct->outfile_fd >= 0)
		close(cmd_struct->outfile_fd);
	cmd_struct->outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd_struct->outfile_fd < 0)
	{
		ft_msg(outfile);
		cmd_struct->outfile_fd = -2;
		g_global->g_last_return_code = 1;
	}
	free(outfile);
	nb->j += 2;
}

void	ft_case_dbleft_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	char	*limiter;

	limiter = ft_substitute_str(minishell->cmd_lst[i][nb->j + 1]);
	if (cmd_struct->infile_fd >= 0)
		close(cmd_struct->infile_fd);
	ft_here_doc(cmd_struct, limiter);
	if (cmd_struct->infile_fd < 0)
	{
		if (cmd_struct->infile_fd != -2)
			ft_msg("here_doc");
		cmd_struct->infile_fd = -2;
		g_global->g_last_return_code = 1;
	}
	free(limiter);
	nb->j += 2;
}

void	ft_case_dright_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb)
{
	char	*outfile;

	outfile = ft_substitute_str(minishell->cmd_lst[i][nb->j + 1]);
	if (cmd_struct->outfile_fd >= 0)
		close(cmd_struct->outfile_fd);
	cmd_struct->outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd_struct->outfile_fd < 0)
	{
		ft_msg(outfile);
		cmd_struct->outfile_fd = -2;
		g_global->g_last_return_code = 1;
	}
	free(outfile);
	nb->j += 2;
}

void	ft_build_struct_cmd(t_mini *minishell, t_cmd *cmd_struct, int i)
{
	t_nb	*nb;

	nb = malloc(sizeof(*nb));
	ft_check_malloc(nb);
	if (ft_check_chevron(minishell, cmd_struct, i, nb) == 1)
		return ;
	nb->j = 0;
	while (cmd_struct->cmd_arg && cmd_struct->cmd_arg[nb->j] != NULL)
	{
		if (ft_strchr(cmd_struct->cmd_arg[nb->j], '~') != NULL)
			cmd_struct->cmd_arg[nb->j] = ft_replace_tilde(\
			cmd_struct->cmd_arg[nb->j], minishell);
		nb->j++;
	}
	ft_remove_quotes(cmd_struct->cmd_arg);
	if (cmd_struct->infile_fd < 0)
		cmd_struct->infile_fd = -1;
	if (cmd_struct->outfile_fd < 0)
		cmd_struct->outfile_fd = -1;
	free(nb);
}
