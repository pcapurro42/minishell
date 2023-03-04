/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_one_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:07:23 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/04 20:09:29 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child_dup_one_cmd(t_cmd *cmd_struct)
{
	if (cmd_struct->infile_fd != -1)
	{
		dup2(cmd_struct->infile_fd, STDIN_FILENO);
		close(cmd_struct->infile_fd);
	}
	else
		dup2(0, STDIN_FILENO);
	if (cmd_struct->outfile_fd != -1)
	{
		dup2(cmd_struct->outfile_fd, STDOUT_FILENO);
		close(cmd_struct->outfile_fd);
	}
	else
		dup2(1, STDOUT_FILENO);
}

static void	ft_check_builtins_one_cmd(t_mini *minishell, t_cmd *cmd_struct)
{
	if (ft_strncmp("echo", cmd_struct->cmd_arg[0], 5) == 0)
	{
		ft_echo_builtins(cmd_struct->cmd_arg);
		unlink("minishell_here_doc.tmp");
	}
	if (ft_strncmp("env", cmd_struct->cmd_arg[0], 4) == 0)
	{
		ft_env_builtins(minishell->mini_tools->envp);
		unlink("minishell_here_doc.tmp");
	}
	if (ft_strncmp("pwd", cmd_struct->cmd_arg[0], 4) == 0)
	{
		ft_pwd_builtins(minishell->mini_tools);
		unlink("minishell_here_doc.tmp");
	}
	if (ft_strncmp("export", cmd_struct->cmd_arg[0], 7) == 0)
	{
		ft_export_builtins(cmd_struct->cmd_arg, minishell);
		unlink("minishell_here_doc.tmp");
	}
	minishell->mini_tools->g_last_return_code = 0;
}

static int	ft_is_builtins(t_cmd *cmd_struct)
{
	if (ft_strncmp("echo", cmd_struct->cmd_arg[0], 5) == 0)
		return (0);
	if (ft_strncmp("env", cmd_struct->cmd_arg[0], 4) == 0)
		return (0);
	if (ft_strncmp("pwd", cmd_struct->cmd_arg[0], 4) == 0)
		return (0);
	if (ft_strncmp("export", cmd_struct->cmd_arg[0], 7) == 0)
		return (0);
	return (1);
}

void	ft_exec_one_cmd(t_mini *minishell, int (*fd)[2])
{
	int		status_code;
	t_cmd	*cmd_struct;
	pid_t	*pid;
	
	cmd_struct = ft_init_cmd(minishell);
	ft_build_struct_cmd(minishell, cmd_struct, 0);
	if (!cmd_struct->cmd_arg)
		ft_error();
	ft_child_dup_one_cmd(cmd_struct);
	if (ft_is_builtins(cmd_struct) == 0)
		return (ft_check_builtins_one_cmd(minishell, cmd_struct));
	pid = ft_execution2(fd, minishell);
	wait(0);
	unlink("minishell_here_doc.tmp");
	minishell->mini_tools->g_last_return_code = WEXITSTATUS(status_code);
/*	pid = fork();
	if (pid < 0)
		ft_error();
	if (pid == 0)
	{
		cmd_path = ft_check_access(cmd_struct);
		execve(cmd_path, cmd_struct->cmd_arg, minishell->mini_tools->envp);
		ft_error_msg(minishell->cmd_lst[0][0]);
	}
	waitpid(pid, &status_code, 0);
	unlink("minishell_here_doc.tmp");
	minishell->mini_tools->g_last_return_code = WEXITSTATUS(status_code);*/
}

//Ne pas oublier de FREE !