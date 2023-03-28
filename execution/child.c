/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:53:27 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/28 17:38:28 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child_dup2(int (*fd)[2], int i, t_mini *minishell)
{
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
	ft_child_dup2(fd, i, minishell);
}

static void	ft_check_builtins(t_mini *minishell, t_cmd *cmd_struct)
{
	if (ft_strncmp("echo", cmd_struct->cmd_arg[0], 5) == 0)
		exit(ft_echo_builtins(cmd_struct->cmd_arg));
	if (ft_strncmp("env", cmd_struct->cmd_arg[0], 4) == 0)
		exit(ft_env_builtins(minishell->mini_tools->envp));
	if (ft_strncmp("pwd", cmd_struct->cmd_arg[0], 4) == 0)
		exit(ft_pwd_builtins(minishell->mini_tools));
	if (ft_strncmp("export", cmd_struct->cmd_arg[0], 7) == 0)
		exit(ft_export_builtins(cmd_struct->cmd_arg, minishell));
	if (ft_strncmp("unset", cmd_struct->cmd_arg[0], 6) == 0)
		exit(ft_unset_builtins(minishell, cmd_struct->cmd_arg));
	if (ft_strncmp("cd", cmd_struct->cmd_arg[0], 3) == 0)
		exit(ft_cd_builtins(cmd_struct->cmd_arg, minishell));
	if (ft_strncmp("exit", cmd_struct->cmd_arg[0], 5) == 0)
		ft_exit_builtins(cmd_struct);
}

void	ft_child(int (*fd)[2], int i, t_mini *minishell)
{
	char	*cmd_path;
	t_cmd	*cmd_struct;

	cmd_struct = ft_init_cmd(minishell);
	ft_build_struct_cmd(minishell, cmd_struct, i);
	if (cmd_struct->infile_fd == -2 || cmd_struct->outfile_fd == -2)
		exit(1);
	if (!cmd_struct->cmd_arg)
		exit(0);
	ft_child_dup(fd, i, minishell, cmd_struct);
	ft_check_builtins(minishell, cmd_struct);
	if ((ft_strlen(cmd_struct->cmd_arg[0]) > 1 && \
	cmd_struct->cmd_arg[0][0] == '.' && cmd_struct->cmd_arg[0][1] == '/') || \
	(ft_strchr(cmd_struct->cmd_arg[0], '/')))
		ft_exec_case(cmd_struct->cmd_arg, minishell->mini_tools->envp);
	cmd_path = ft_check_access(cmd_struct);
	execve(cmd_path, cmd_struct->cmd_arg, minishell->mini_tools->envp);
	ft_error_msg(minishell->cmd_lst[0][i]);
}

void	ft_child_one_cmd(int (*fd)[2], int i, \
t_mini *minishell, t_cmd *cmd_struct)
{
	char	*cmd_path;

	if (!cmd_struct->cmd_arg)
		exit(0);
	ft_child_dup(fd, i, minishell, cmd_struct);
	ft_check_builtins(minishell, cmd_struct);
	if ((ft_strlen(cmd_struct->cmd_arg[0]) > 1 && \
	cmd_struct->cmd_arg[0][0] == '.' && cmd_struct->cmd_arg[0][1] == '/') || \
	(ft_strchr(cmd_struct->cmd_arg[0], '/')))
		ft_exec_case(cmd_struct->cmd_arg, minishell->mini_tools->envp);
	cmd_path = ft_check_access(cmd_struct);
	execve(cmd_path, cmd_struct->cmd_arg, minishell->mini_tools->envp);
	ft_error_msg(minishell->cmd_lst[0][i]);
}
