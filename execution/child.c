/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:53:27 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/24 14:01:26 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(int (*fd)[2], int i, t_mini *minishell)
{
	char	*cmd_path;

	if (i == 0)
		dup2(minishell->infile_fd, STDIN_FILENO);
	if (i == minishell->nb_cmd && minishell->outfile_mod != -1)
		dup2(minishell->outfile_fd, STDOUT_FILENO);
	if (i == 0 && i != minishell->nb_cmd - 1)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);
	}
	if (i != 0 && i == minishell->nb_cmd - 1)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
	if (i != 0 && i != minishell->nb_cmd - 1)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
	close(minishell->infile_fd);
	close(minishell->outfile_fd);
/*	if ((ft_strlen(minishell->cmd_lst[i][0]) > 1 && minishell->cmd_lst[i][0][0] == '.' && \
	minishell->cmd_lst[i][0][1] == '/') || (ft_strchr(&(minishell->cmd_lst[i][0][2]), '/') && \
	ft_strnstr(minishell->cmd_lst[i][0], ".sh", ft_strlen(minishell->cmd_lst[i][0])) != NULL))
		exec_case(i, minishell);
	else if (minishell->cmd_lst[i][0], ".sh", \
	ft_strlen(minishell->cmd_lst[i][0]) != NULL)
		cmd_error(minishell->cmd_lst[i][0]);*/
	cmd_path = ft_check_access(i, minishell);
	execve(cmd_path, minishell->cmd_lst[i], minishell->envp);
	ft_error_msg(minishell->cmd_lst[0][i]);
}
