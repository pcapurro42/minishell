/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:55:57 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/05 16:46:10 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_builtins(t_cmd *cmd_struct)
{
	char	*temp;
	char	*temp2;

	ft_putstr_fd("exit\n", 2);
	if (!(cmd_struct->cmd_arg[1]))
		exit(0);
	else if (ft_isnum(cmd_struct->cmd_arg[1]))
		exit(ft_atoi(cmd_struct->cmd_arg[1]) % 256);
	else
	{
		temp = ft_strjoin("minishell: exit: ", cmd_struct->cmd_arg[1]);
		temp2 = ft_strjoin(temp, ": numeric argument required\n");
		ft_putstr_fd(temp2, 2);
		exit(255);
	}
}