/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:53:27 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/01 16:06:28 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_here_doc(t_cmd *cmd_struct, char *limiter)
{
	char	*gnl;

	cmd_struct->infile_fd = open("minishell_here_doc.tmp", \
	O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd_struct->infile_fd < 0)
		return ;
	write(0, "> ", 2);
	gnl = get_next_line(0);
	ft_check_malloc(gnl);
	while (ft_strncmp(gnl, limiter, ft_strlen(gnl)) != '\n')
	{
		write(cmd_struct->infile_fd, gnl, ft_strlen(gnl));
		free(gnl);
		write(0, "> ", 2);
		gnl = get_next_line(0);
		ft_check_malloc(gnl);
	}
	free(gnl);
	close(cmd_struct->infile_fd);
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

static void	ft_child_dup(int (*fd)[2], int i, t_mini *minishell, t_cmd *cmd_struct)
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
	if (cmd_struct->infile_fd != -1)
		close(cmd_struct->infile_fd);
	if (cmd_struct->outfile_fd != -1)
		close(cmd_struct->infile_fd);
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

void	ft_build_struct_cmd(t_mini *minishell, t_cmd *cmd_struct, int i)
{
	char	**temp;
	int		j;
	int		nb_str_to_add;
	int		len_cmd_arg;
	int		id_str_to_add;

	j = 0;
	len_cmd_arg = 0;
	while (minishell->cmd_lst[i][j])
	{
		if (ft_strncmp(minishell->cmd_lst[i][j], "<", 2) == 0)
		{
			if (cmd_struct->infile_fd >= 0)
				close(cmd_struct->infile_fd);
			cmd_struct->infile_fd = open(minishell->cmd_lst[i][j + 1], O_RDONLY);
			if (cmd_struct->infile_fd < 0)
				file_not_open(cmd_struct, minishell->cmd_lst[i][j + 1]);
			j += 2;
		}
		else if (ft_strncmp(minishell->cmd_lst[i][j], ">", 2) == 0)
		{
			if (cmd_struct->outfile_fd >= 0)
				close(cmd_struct->outfile_fd);
			cmd_struct->outfile_fd = open(minishell->cmd_lst[i][j + 1], \
			O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (cmd_struct->outfile_fd < 0)
				perror(minishell->cmd_lst[i][j + 1]);
			j += 2;
		}
		else if (ft_strncmp(minishell->cmd_lst[i][j], "<<", 3) == 0)
		{
			if (cmd_struct->infile_fd >= 0)
				close(cmd_struct->infile_fd);
			ft_here_doc(cmd_struct, \
				minishell->cmd_lst[i][j + 1]);
			j += 2;
		}
		else if (ft_strncmp(minishell->cmd_lst[i][j], ">>", 3) == 0)
		{
			if (cmd_struct->outfile_fd >= 0)
				close(cmd_struct->outfile_fd);
			cmd_struct->outfile_fd = open(minishell->cmd_lst[i][j + 1], \
			O_CREAT | O_RDWR | O_APPEND, 0644);;
			if (cmd_struct->outfile_fd < 0)
				perror(minishell->cmd_lst[i][j + 1]);
			j += 2;
		}
		else
		{
			nb_str_to_add = 0;
			while (minishell->cmd_lst[i][j + nb_str_to_add] &&
			ft_strncmp(minishell->cmd_lst[i][j + nb_str_to_add], "<", 2) != 0 && \
			ft_strncmp(minishell->cmd_lst[i][j + nb_str_to_add], ">", 2) != 0 && \
			ft_strncmp(minishell->cmd_lst[i][j + nb_str_to_add], "<<", 3) != 0 && \
			ft_strncmp(minishell->cmd_lst[i][j + nb_str_to_add], ">>", 3) != 0)
				nb_str_to_add++;
			if (!cmd_struct->cmd_arg)
				cmd_struct->cmd_arg = malloc(\
					sizeof(*cmd_struct->cmd_arg) * (nb_str_to_add + 1));
			else
			{
				temp = malloc(sizeof(*temp) * \
					(nb_str_to_add + len_cmd_arg + 1));
				len_cmd_arg = 0;
				while (cmd_struct->cmd_arg[len_cmd_arg])
				{
					temp[len_cmd_arg] = cmd_struct->cmd_arg[len_cmd_arg];
					len_cmd_arg++;
				}
				free(cmd_struct->cmd_arg);
				cmd_struct->cmd_arg = temp;
				cmd_struct->cmd_arg[len_cmd_arg] = NULL;
			}
			id_str_to_add = 0;
			while (id_str_to_add < nb_str_to_add)
			{
				cmd_struct->cmd_arg[len_cmd_arg] = minishell->cmd_lst[i][j];
				j++;
				len_cmd_arg++;
				id_str_to_add++;
			}
			cmd_struct->cmd_arg[len_cmd_arg] = NULL;
		}
	}
	if (cmd_struct->infile_fd < 0)
		cmd_struct->infile_fd = -1;
	if (cmd_struct->outfile_fd < 0)
		cmd_struct->outfile_fd = -1;
}

void	ft_child(int (*fd)[2], int i, t_mini *minishell)
{
	char	*cmd_path;
	t_cmd	*cmd_struct;

	cmd_struct = ft_init_cmd(minishell);
	ft_build_struct_cmd(minishell, cmd_struct, i);
	ft_child_dup(fd, i, minishell, cmd_struct);
	if (!cmd_struct->cmd_arg)
		exit(0);
	cmd_path = ft_check_access(cmd_struct);
	execve(cmd_path, cmd_struct->cmd_arg, minishell->envp);
	ft_error_msg(minishell->cmd_lst[0][i]);
}

// CHECK .sh files

/*	if ((ft_strlen(minishell->cmd_lst[i][0]) > 1 && \
		minishell->cmd_lst[i][0][0] == '.' && \
		minishell->cmd_lst[i][0][1] == '/') || \
		(ft_strchr(&(minishell->cmd_lst[i][0][2]), '/') && \
		ft_strnstr(minishell->cmd_lst[i][0], ".sh", \
		(minishell->cmd_lst[i][0])) != NULL))
		exec_case(i, minishell);
	else if (minishell->cmd_lst[i][0], ".sh", \
	ft_strlen(minishell->cmd_lst[i][0]) != NULL)
		cmd_error(minishell->cmd_lst[i][0]);*/
