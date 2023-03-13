/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:43:59 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/13 04:21:47 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd_builtins(t_mini_tools *mini_tools)
{
	ft_putstr_fd(mini_tools->pwd, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

char	*ft_get_pwd(char **envp)
{
	int		i;
	char	*pwd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	pwd = ft_strdup(&(envp[i][4]));
	ft_check_malloc(pwd);
	return (pwd);
}