/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:47:08 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/29 13:21:00 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipex_close_files(int (*fd)[2], int i)
{
	close(fd[i - 1][0]);
	close(fd[i - 1][1]);
}

void	ft_child_choice(int (*fd)[2], \
t_mini *minishell, t_cmd *cmd_struct, int i)
{
	if (minishell->nb_cmd == 1)
		ft_child_one_cmd(fd, i, minishell, cmd_struct);
	else
		ft_child(fd, i, minishell);
}

static pid_t	*ft_execution2(int (*fd)[2], \
t_mini *minishell, t_cmd *cmd_struct)
{
	pid_t	*pid;
	int		i;

	pid = malloc(sizeof(*pid) * (minishell->nb_cmd));
	ft_check_malloc(pid);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		if ((i != minishell->nb_cmd - 1) && pipe(fd[i]))
			ft_error();
		pid[i] = fork();
		if (pid[i] < 0)
			ft_error();
		if (pid[i] == 0)
			ft_child_choice(fd, minishell, cmd_struct, i);
		if (minishell->nb_cmd == 1)
			ft_destroy_cmd(cmd_struct);
		g_global->g_pid = pid[i];
		if (i > 0)
			ft_pipex_close_files(fd, i);
		i++;
	}
	return (pid);
}

void	ft_execution3(t_mini *minishell, t_cmd *cmd_struct)
{
	pid_t	*pid;
	int		(*fd)[2];
	int		*status_code;
	int		i;

	status_code = malloc(sizeof(*status_code) * minishell->nb_cmd);
	ft_check_malloc(status_code);
	fd = malloc(sizeof(*fd) * (minishell->nb_cmd - 1));
	ft_check_malloc(fd);
	pid = ft_execution2(fd, minishell, cmd_struct);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		waitpid(pid[i], &(status_code[i]), 0);
		i++;
	}
	if (g_global->g_last_return_code >= 0)
		g_global->g_last_return_code = WEXITSTATUS(status_code[i - 1]);
	else
		g_global->g_last_return_code = g_global->g_last_return_code * (-1);
	g_global->g_pid = -2147483648;
	free(fd);
	free(status_code);
	free(pid);
}

void	ft_execution(t_mini *minishell)
{
	t_cmd	*cmd_struct;
	int		i;

	i = 0;
	while (minishell->cmd_lst && minishell->cmd_lst[i] != NULL)
		i++;
	minishell->nb_cmd = i;
	if (minishell->nb_cmd == 0)
		return ;
	if (minishell->nb_cmd == 1)
	{
		cmd_struct = ft_exec_one_cmd(minishell);
		if (cmd_struct == NULL || cmd_struct->infile_fd == -2 || \
		cmd_struct->outfile_fd == -2)
		{
			ft_destroy_cmd(cmd_struct);
			return ;
		}
	}
	else
		cmd_struct = NULL;
	ft_execution3(minishell, cmd_struct);
}
