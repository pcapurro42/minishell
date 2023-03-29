/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_one_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:07:23 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/29 10:37:31 by vdelafos         ###   ########.fr       */
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
	char	*temp;

	temp = ft_lower_input(cmd_struct->cmd_arg[0]);
	free(cmd_struct->cmd_arg[0]);
	cmd_struct->cmd_arg[0] = temp;
	if (ft_strncmp("echo", temp, 5) == 0)
		g_global->g_last_return_code = ft_echo_builtins(cmd_struct->cmd_arg);
	if (ft_strncmp("env", temp, 4) == 0)
		g_global->g_last_return_code = ft_env_builtins \
		(minishell->mini_tools->envp);
	if (ft_strncmp("pwd", temp, 4) == 0)
		g_global->g_last_return_code = ft_pwd_builtins(minishell->mini_tools);
	if (ft_strncmp("export", temp, 7) == 0)
		g_global->g_last_return_code = ft_export_builtins \
		(cmd_struct->cmd_arg, minishell);
	if (ft_strncmp("unset", temp, 6) == 0)
		g_global->g_last_return_code = ft_unset_builtins \
		(minishell, cmd_struct->cmd_arg);
	if (ft_strncmp("cd", temp, 3) == 0)
		g_global->g_last_return_code = ft_cd_builtins \
		(cmd_struct->cmd_arg, minishell);
	if (ft_strncmp("exit", temp, 5) == 0)
		ft_exit_builtins(cmd_struct);
}

static int	ft_is_builtins(t_cmd *cmd_struct)
{
	char	*temp;
	int		is_builtins;
	
	is_builtins = 1;
	temp = ft_lower_input(cmd_struct->cmd_arg[0]);
	if (ft_strncmp("echo", temp, 5) == 0)
		is_builtins = 0;
	if (ft_strncmp("env", temp, 4) == 0)
		is_builtins = 0;
	if (ft_strncmp("pwd", temp, 4) == 0)
		is_builtins = 0;
	if (ft_strncmp("export", temp, 7) == 0)
		is_builtins = 0;
	if (ft_strncmp("unset", temp, 6) == 0)
		is_builtins = 0;
	if (ft_strncmp("cd", temp, 3) == 0)
		is_builtins = 0;
	if (ft_strncmp("exit", temp, 5) == 0)
		is_builtins = 0;
	free(temp);
	if (is_builtins == 0)
		return (0);
	else
		return (1);
}

t_cmd	*ft_exec_one_cmd(t_mini *minishell)
{
	t_cmd	*cmd_struct;
	int		old_stdin;
	int		old_stdout;

	cmd_struct = ft_init_cmd(minishell);
	ft_build_struct_cmd(minishell, cmd_struct, 0);
	if (!cmd_struct->cmd_arg || cmd_struct->infile_fd == -2 || \
	cmd_struct->outfile_fd == -2 || ft_is_builtins(cmd_struct) == 1)
		return (cmd_struct);
	old_stdin = dup(0);
	old_stdout = dup(1);
	ft_child_dup_one_cmd(cmd_struct);
	ft_check_builtins_one_cmd(minishell, cmd_struct);
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdin);
	close(old_stdout);
	ft_destroy_cmd(cmd_struct);
	return (NULL);
}
