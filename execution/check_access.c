/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:51:59 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/07 17:43:15 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_check_access(t_cmd *cmd_struct)
{
	int		j;
	char	*cmd_path;
	char	*error_msg;

	j = 0;
	while (cmd_struct->cmd_path_lst[j])
	{
		cmd_path = ft_strjoin(cmd_struct->cmd_path_lst[j], \
			cmd_struct->cmd_arg[0]);
		ft_check_malloc(cmd_path);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		j++;
	}
	if (access(cmd_struct->cmd_arg[0], F_OK) == 0 && \
		access(cmd_struct->cmd_arg[0], X_OK) == 0)
		return (cmd_struct->cmd_arg[0]);
	cmd_path = ft_strjoin(cmd_struct->cmd_arg[0], ": command not found\n");
	ft_check_malloc(cmd_path);
	error_msg = ft_strjoin("minishell: ", cmd_path);
	ft_check_malloc(error_msg);
	write(2, error_msg, ft_strlen(error_msg));
	unlink("minishell_here_doc.tmp");
	exit(127);
}
