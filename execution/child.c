/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:53:27 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/03 15:28:11 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child_dup2(int (*fd)[2], int i, t_mini *minishell, \
	t_cmd *cmd_struct)
{
	if (cmd_struct->infile_fd != -1)
		close(cmd_struct->infile_fd);
	if (cmd_struct->outfile_fd != -1)
		close(cmd_struct->infile_fd);
	if (i != 0)
	{
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
	if (i != minishell->nb_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

static void	ft_child_dup(int (*fd)[2], int i, t_mini *minishell, \
	t_cmd *cmd_struct)
{
	if (cmd_struct->infile_fd != -1)
	{
		dup2(cmd_struct->infile_fd, STDIN_FILENO);
		close(cmd_struct->infile_fd);
	}
	else if (i != 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	else
		dup2(0, STDIN_FILENO);
	if (cmd_struct->outfile_fd != -1)
	{
		dup2(cmd_struct->outfile_fd, STDOUT_FILENO);
		close(cmd_struct->outfile_fd);
	}
	else if (i != minishell->nb_cmd - 1)
		dup2(fd[i][1], STDOUT_FILENO);
	else
		dup2(1, STDOUT_FILENO);
	ft_child_dup2(fd, i, minishell, cmd_struct);
}

void	ft_check_builtins(t_mini *minishell, t_cmd *cmd_struct)
{
	if (ft_strncmp("echo", cmd_struct->cmd_arg[0], 5) == 0)
	{
		ft_echo_builtins(cmd_struct->cmd_arg);
		unlink("minishell_here_doc.tmp");
		exit(0);
	}
	else if (ft_strncmp("env", cmd_struct->cmd_arg[0], 4) == 0)
	{
		ft_env_builtins(minishell->envp);
		unlink("minishell_here_doc.tmp");
		exit(0);
	}
}

void	ft_child(int (*fd)[2], int i, t_mini *minishell)
{
	char	*cmd_path;
	t_cmd	*cmd_struct;

	cmd_struct = ft_init_cmd(minishell);
	ft_build_struct_cmd(minishell, cmd_struct, i);
	ft_child_dup(fd, i, minishell, cmd_struct);
	if (!cmd_struct->cmd_arg)
		exit(0);
	ft_check_builtins(minishell, cmd_struct);
	cmd_path = ft_check_access(cmd_struct);
	execve(cmd_path, cmd_struct->cmd_arg, minishell->envp);
	ft_error_msg(minishell->cmd_lst[0][i]);
}

// CHECK .sh files

/*	if ((ft_strlen(minishell->cmd_lst[i][0]) > 1 && \
		minishell->cmd_lst[i][0][0] == '.' && \
		minishell->cmd_lst[i][0][1] == '/') || \
		(ft_strchr(&(minishell->cmd_lst[i][0][2]), '/') && \
		ft_strnstr(minishell->cmd_lst[i][0], ".sh", \
		(minishell->cmd_lst[i][0])) != NULL))
		exec_case(i, minishell);
	else if (minishell->cmd_lst[i][0], ".sh", \
	ft_strlen(minishell->cmd_lst[i][0]) != NULL)
		cmd_error(minishell->cmd_lst[i][0]);*/
