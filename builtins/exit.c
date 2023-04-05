/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:55:57 by vdelafos          #+#    #+#             */
/*   Updated: 2023/04/05 12:08:30 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_llint(char	*nb)
{
	int	i;

	i = 0;
	if (nb[0] == '-' || nb[1] == '+')
		i++;
	while (nb[i] == '0')
		i++;
	if (nb[0] == '-' && \
	((ft_strlen(&(nb[i])) == ft_strlen("9223372036854775808") \
	&& ft_strncmp(&(nb[i]), "9223372036854775808", ft_strlen(&(nb[i]))) > 0) \
	|| (ft_strlen(&(nb[i])) > ft_strlen("9223372036854775808"))))
		return (1);
	if ((ft_isdigit(nb[0]) || nb[0] == '+') && \
	((ft_strlen(&(nb[i])) == ft_strlen("9223372036854775807") && \
	ft_strncmp(&(nb[i]), "9223372036854775807", ft_strlen(&(nb[i]))) > 0) || \
	(ft_strlen(&(nb[i])) > ft_strlen("9223372036854775807"))))
		return (1);
	return (0);
}

void	ft_exit_builtins(t_cmd *cmd_struct, t_mini *minishell)
{
	char	*temp;
	char	*temp2;

	if (minishell->nb_cmd == 1)
		ft_putstr_fd("exit\n", 1);
	if (!(cmd_struct) || !(cmd_struct->cmd_arg[1]))
		exit(0);
	else if (ft_isnum(cmd_struct->cmd_arg[1]) && \
	ft_is_llint(cmd_struct->cmd_arg[1]) == 0)
		exit(ft_atoll(cmd_struct->cmd_arg[1]) % 256);
	else
	{
		temp = ft_strjoin("minishell: exit: ", cmd_struct->cmd_arg[1]);
		temp2 = ft_strjoin(temp, ": numeric argument required\n");
		ft_putstr_fd(temp2, 2);
		exit(255);
	}
}
