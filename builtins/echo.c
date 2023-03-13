/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:55:20 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/13 04:22:41 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_builtins(char **cmd_lst)
{
	int	i;
	int	j;
	int	final_line_break;

	i = 1;
	final_line_break = 0;
	while (cmd_lst[i] && ft_strncmp(cmd_lst[i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd_lst[i][j] == 'n')
			j++;
		if (cmd_lst[i][j] != '\0')
			break ;
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
	return (0);
}
