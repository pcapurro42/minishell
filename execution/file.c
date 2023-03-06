/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:59:38 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/06 18:36:24 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_here_doc(t_cmd *cmd_struct, char *limiter)
{
	int		pid;
	char	*gnl;

	pid = fork();
	if (pid < 0)
		ft_error();
	if (pid == 0)
	{
		cmd_struct->infile_fd = open("minishell_here_doc.tmp", \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmd_struct->infile_fd < 0)
			ft_error();
		write(1, "> ", 2);
		gnl = get_next_line(0);
		if (!gnl)
			exit(0);
		while (ft_strncmp(gnl, limiter, ft_strlen(gnl)) != '\n')
		{
			write(cmd_struct->infile_fd, gnl, ft_strlen(gnl));
			free(gnl);
			write(1, "> ", 2);
			gnl = get_next_line(0);
			if (!gnl)
				exit(0);
		}
		free(gnl);
		close(cmd_struct->infile_fd);
		exit(0);
	}
	global_pid = pid;
	waitpid(pid, NULL, 0);
	global_pid = -1;
	cmd_struct->infile_fd = open("minishell_here_doc.tmp", O_RDONLY);
	return ;
}

void	file_not_open(t_cmd *cmd_struct, char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file_name);
	cmd_struct->infile_fd = open("minishell_here_doc.tmp", \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd_struct->infile_fd < 0)
		ft_error();
	close(cmd_struct->infile_fd);
	cmd_struct->infile_fd = open("minishell_here_doc.tmp", O_RDONLY);
	return ;
}
