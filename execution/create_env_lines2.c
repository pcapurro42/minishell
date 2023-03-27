/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_lines2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:11:33 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/27 10:27:15 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_nb_missing_lines(char **envp)
{
	int	nb_missing_lines;

	nb_missing_lines = ft_find_line_env(envp, "PWD=") + \
	ft_find_line_env(envp, "SHLVL=") + ft_find_line_env(envp, "_=") + \
	ft_find_line_env(envp, "OLDPWD=");
	return (nb_missing_lines);
}

char	*ft_getoldpwd(void)
{
	char	*oldpwd;

	oldpwd = malloc(sizeof(*oldpwd) * 7);
	ft_check_malloc(oldpwd);
	oldpwd[0] = 'O';
	oldpwd[1] = 'L';
	oldpwd[2] = 'D';
	oldpwd[3] = 'P';
	oldpwd[4] = 'W';
	oldpwd[5] = 'D';
	oldpwd[6] = '\0';
	return (oldpwd);
}
