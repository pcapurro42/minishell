/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:47:08 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/07 10:51:45 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipex_close_files(int (*fd)[2], int i)
{
	close(fd[i - 1][0]);
	close(fd[i - 1][1]);
}

static pid_t	*ft_execution2(int (*fd)[2], t_mini *minishell, t_cmd *cmd_struct)
{
	pid_t	*pid;
	int		i;

	pid = malloc(sizeof(*pid) * (minishell->nb_cmd));
	if (pid == NULL)
		ft_error();
	i = 0;
	while (i < minishell->nb_cmd)
	{
		if ((i != minishell->nb_cmd - 1) && pipe(fd[i]))
			ft_error();
		pid[i] = fork();
		if (pid[i] < 0)
			ft_error();
		if (pid[i] == 0)
		{
			if (minishell->nb_cmd == 1)
				ft_child_one_cmd(fd, i, minishell, cmd_struct);
			else
				ft_child(fd, i, minishell);
		}
		global_pid = pid[i];
		if (i > 0)
			ft_pipex_close_files(fd, i);
		i++;
	}
	return (pid);
}

void	ft_execution(t_mini *minishell)
{
	pid_t	*pid;
	int		(*fd)[2];
	int		*status_code;
	int		i;
	t_cmd 	*cmd_struct;

	i = 0;
	while (minishell->cmd_lst && minishell->cmd_lst[i] != NULL)
		i++;
	minishell->nb_cmd = i;
	if (minishell->nb_cmd == 0)
		return ;
	if (minishell->nb_cmd == 1)
	{
		cmd_struct = ft_exec_one_cmd(minishell);
		if (cmd_struct == NULL)
			return ;
	}
	else
		cmd_struct = NULL;
	status_code = malloc(sizeof(*status_code) * minishell->nb_cmd);
	fd = malloc(sizeof(*fd) * (minishell->nb_cmd - 1));
	if (status_code == NULL || fd == NULL)
		ft_error();
	pid = ft_execution2(fd, minishell, cmd_struct);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		waitpid(pid[i], &(status_code[i]), 0);
		i++;
	}
	global_pid = -1;
	minishell->mini_tools->main_pid = -1;
	unlink("minishell_here_doc.tmp");
	minishell->mini_tools->g_last_return_code = WEXITSTATUS(status_code[i - 1]);
}
