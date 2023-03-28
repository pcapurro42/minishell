/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:51:59 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/28 17:38:40 by vdelafos         ###   ########.fr       */
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
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		j++;
	}
	cmd_path = ft_strjoin(cmd_struct->cmd_arg[0], ": command not found\n");
	error_msg = ft_strjoin("minishell: ", cmd_path);
	write(2, error_msg, ft_strlen(error_msg));
	exit(127);
}
