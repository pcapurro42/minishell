/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:47:08 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/04 17:52:24 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipex_close_files(int (*fd)[2], int i)
{
	close(fd[i - 1][0]);
	close(fd[i - 1][1]);
}

static pid_t	*ft_execution2(int (*fd)[2], t_mini *minishell)
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
			ft_child(fd, i, minishell);
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

	i = 0;
	while (minishell->cmd_lst && minishell->cmd_lst[i] != NULL)
		i++;
	minishell->nb_cmd = i;
	if (minishell->nb_cmd == 0)
		return ;
	if (minishell->nb_cmd == 1)
		return (ft_exec_one_cmd(minishell));
	status_code = malloc(sizeof(*status_code) * minishell->nb_cmd);
	fd = malloc(sizeof(*fd) * (minishell->nb_cmd - 1));
	if (status_code == NULL || fd == NULL)
		ft_error();
	pid = ft_execution2(fd, minishell);
	i = 0;
	while (i < minishell->nb_cmd)
	{
		waitpid(pid[i], &(status_code[i]), 0);
		i++;
	}
	unlink("minishell_here_doc.tmp");
	minishell->mini_tools->g_last_return_code = WEXITSTATUS(status_code[i - 1]);
}
