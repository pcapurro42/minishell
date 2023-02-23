/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:08:47 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/23 10:57:14 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_here_doc(t_mini *minishell)
{
	char	*gnl;

	minishell->infile_fd = open("minishell_here_doc.tmp", \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (minishell->infile_fd < 0)
		return ;
	write(0, "> ", 1);
	gnl = get_next_line(0);
	ft_check_malloc(gnl);
	while (ft_strncmp(gnl, minishell->limiter, ft_strlen(gnl)) != '\n')
	{
		write(minishell->infile_fd, gnl, ft_strlen(gnl));
		free(gnl);
		write(0, "> ", 14);
		gnl = get_next_line(0);
		ft_check_malloc(gnl);
	}
	free(gnl);
	close(minishell->infile_fd);
	minishell->infile_fd = open("minishell_here_doc.tmp", O_RDONLY);
	return ;
}

void	file_not_open(t_mini *minishell)
{
	ft_putstr_fd("minishell: ", 2);
	perror(minishell->infile);
	minishell->infile_fd = open("minishell_here_doc.tmp", \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (minishell->infile_fd < 0)
		ft_error();
	close(minishell->infile_fd);
	minishell->infile_fd = open("minishell_here_doc.tmp", O_RDONLY);
	return ;
}

void	ft_execution(t_mini *minishell)
{
	if (minishell->nb_cmd == 0)
		return ;
	if (minishell->infile_mod == 1)
		ft_here_doc(minishell);
	if (minishell->infile_mod == 0)
		minishell->infile_fd = open(minishell->infile, O_RDONLY);
	if (minishell->infile_fd < 0)
		file_not_open(minishell);
	if (minishell->infile_fd < 0)
		ft_error_msg(minishell->infile);
	if (minishell->outfile_mod == 1)
		minishell->outfile_fd = open(minishell->outfile, \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (minishell->outfile_mod == 0)
		minishell->outfile_fd = open(minishell->outfile, \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (minishell->outfile_fd < 0)
		ft_error_msg(minishell->outfile);
	/*else if (minishell->nb_cmd == 1)
		ft_pipex_one_cmd(minishell);
	else
		ft_pipex_multiple_cmd(minishell);*/
}	

