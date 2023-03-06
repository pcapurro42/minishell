/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:14:19 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/28 20:54:55 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_msg(char *msg)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: ", msg);
	ft_check_malloc(error_msg);
	perror(error_msg);
	unlink("minishell_here_doc.tmp");
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	write(2, "minishell: Error\n", 17);
	unlink("minishell_here_doc.tmp");
	exit(EXIT_FAILURE);
}

void	ft_cmd_error(char **cmd)
{
	char	*temp;
	char	*error_msg;

	temp = ft_strjoin(cmd[0], ": command not found\n");
	ft_check_malloc(temp);
	error_msg = ft_strjoin("minishell: ", temp);
	ft_check_malloc(error_msg);
	write(2, error_msg, ft_strlen(error_msg));
	unlink("minishell_here_doc.tmp");
	exit(127);
}

void	ft_check_malloc(void *str)
{
	if (str == NULL)
		ft_error();
}
