/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:43:59 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/03 17:05:41 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd_builtins(t_mini_tools *mini_tools, char **cmd_arg)
{
	if (cmd_arg[1])
		ft_putstr_fd("minishell: pwd: too many arguments", 1);
	else
		ft_putstr_fd(mini_tools->pwd, 1);
	ft_putchar_fd('\n', 1);
}

char	*ft_get_pwd(char **envp)
{
	int		i;
	char	*pwd;

	i = 0;
	if (!envp)
		return (getenv("PWD"));
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	if (!(envp[i]))
		return (getenv("PWD"));
	pwd = ft_strdup(&(envp[i][4]));
	if (pwd == NULL)
		return (getenv("PWD"));
	return (pwd);
}