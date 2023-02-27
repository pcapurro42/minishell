/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:55:20 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/27 11:41:54 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_builtins(char **cmd_lst)
{
	int	i;
	int	final_line_break;

	i = 1;
	final_line_break = 0;
	while (ft_strncmp(cmd_lst[i], "-n", 3) == 0)
	{
		final_line_break = 1;
		i++;
	}
	while (cmd_lst[i])
	{
		ft_putstr_fd(cmd_lst[i], 1);
		if (cmd_lst[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (final_line_break == 0)
		ft_putstr_fd("\n", 1);
}
