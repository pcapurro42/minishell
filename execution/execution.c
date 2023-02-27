/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:08:47 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/27 11:07:13 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_here_doc(t_mini *minishell)
{
	char	*gnl;

	minishell->infile_fd = open("minishell_here_doc.tmp", \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (minishell->infile_fd < 0)
		return ;
	write(0, "> ", 2);
	gnl = get_next_line(0);
	ft_check_malloc(gnl);
	while (ft_strncmp(gnl, minishell->limiter, ft_strlen(gnl)) != '\n')
	{
		write(minishell->infile_fd, gnl, ft_strlen(gnl));
		free(gnl);
		write(0, "> ", 2);
		gnl = get_next_line(0);
		ft_check_malloc(gnl);
	}
	free(gnl);
	close(minishell->infile_fd);
	minishell->infile_fd = open("minishell_here_doc.tmp", O_RDONLY);
	return ;
}

static void	file_not_open(t_mini *minishell)
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
	if (minishell->infile_fd < 0 && minishell->infile_mod != -1)
		file_not_open(minishell);
	if (minishell->infile_fd < 0 && minishell->infile_mod != -1)
		ft_error_msg(minishell->infile);
	if (minishell->outfile_mod == 1)
		minishell->outfile_fd = open(minishell->outfile, \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (minishell->outfile_mod == 0)
		minishell->outfile_fd = open(minishell->outfile, \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (minishell->outfile_fd < 0 && minishell->outfile_mod != -1)
		ft_error_msg(minishell->outfile);
	ft_pipex(minishell);
}	

// Check l'existence des commandes avant celle des fichiers
// afin de respecter l'ordre de shell