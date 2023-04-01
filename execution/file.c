/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:59:38 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/16 22:54:13 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_here_doc_fork(char *limiter, int pipe_fd[2])
{
	char	*input;

	input = readline("> ");
	if (!input)
		exit(0);
	while (ft_strncmp(input, limiter, ft_strlen(input)) != '\n')
	{
		write(pipe_fd[1], input, ft_strlen(input));
		free(input);
		input = readline("> ");
		if (!input)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(0);
		}
	}
	free(input);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(0);
}

void	ft_here_doc(t_cmd *cmd_struct, char *limiter)
{
	int		pid;
	int		pipe_fd[2];
	int		status_code;

	if (pipe(pipe_fd))
		ft_error();
	pid = fork();
	if (pid < 0)
		ft_error();
	if (pid == 0)
		ft_here_doc_fork(limiter, pipe_fd);
	close(pipe_fd[1]);
	g_global->g_pid = (0 - pid);
	waitpid(pid, &status_code, 0);
	g_global->g_pid = -2147483648;
	if (g_global->g_last_return_code != -1)
		cmd_struct->infile_fd = pipe_fd[0];
	else
	{
		close(pipe_fd[0]);
		cmd_struct->infile_fd = -2;
	}
	return ;
}
