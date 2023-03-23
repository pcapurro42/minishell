/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:14:19 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/16 02:22:35 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_msg(char *msg)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: ", msg);
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	ft_cmd_error(char **cmd)
{
	char	*temp;
	char	*error_msg;

	temp = ft_strjoin(cmd[0], ": command not found\n");
	error_msg = ft_strjoin("minishell: ", temp);
	write(2, error_msg, ft_strlen(error_msg));
	exit(127);
}

void	ft_msg(char	*msg)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: ", msg);
	perror(error_msg);
	free(error_msg);
}
