/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:14:19 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/22 13:14:51 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *msg)
{
	char	*error_msg;

	error_msg = ft_strjoin("pipex: ", msg);
	check_malloc(error_msg);
	perror(error_msg);
	unlink("here_doc");
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	write(2, "pipex: Error\n", 13);
	unlink("here_doc");
	exit(EXIT_FAILURE);
}

void	cmd_error(char **cmd)
{
	char	*temp;
	char	*error_msg;

	temp = ft_strjoin(cmd[0], ": command not found\n");
	check_malloc(temp);
	error_msg = ft_strjoin("pipex: ", temp);
	check_malloc(error_msg);
	write(2, error_msg, ft_strlen(error_msg));
	unlink("here_doc");
	exit(127);
}

void	check_malloc(void *str)
{
	if (str == NULL)
		ft_error();
}
