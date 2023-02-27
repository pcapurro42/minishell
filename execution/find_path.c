/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:52:55 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/27 11:11:33 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_complete_path(char **cmd_path_lst)
{
	int		i;
	char	*temp;

	if (cmd_path_lst && cmd_path_lst[0])
	{
		temp = ft_strdup(&(cmd_path_lst[0][5]));
		free(cmd_path_lst[0]);
		cmd_path_lst[0] = temp;
	}
	else
		ft_error();
	ft_check_malloc(cmd_path_lst[0]);
	i = 0;
	while (cmd_path_lst[i])
	{
		temp = ft_strjoin(cmd_path_lst[i], "/");
		ft_check_malloc(temp);
		free(cmd_path_lst[i]);
		cmd_path_lst[i] = temp;
		i++;
	}
}

static char	**ft_no_env(void)
{
	char	**cmd_path_lst;

	cmd_path_lst = malloc(2 * sizeof(*cmd_path_lst));
	if (cmd_path_lst == NULL)
		ft_error();
	cmd_path_lst[0] = "/usr/bin/";
	cmd_path_lst[1] = NULL;
	return (cmd_path_lst);
}

char	**ft_find_path(char *envp[])
{
	char	**cmd_path_lst;
	int		i;

	i = 0;
	if (!envp)
		return (ft_no_env());
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!(envp[i]))
		return (ft_no_env());
	cmd_path_lst = ft_split(envp[i], ':');
	ft_complete_path(cmd_path_lst);
	return (cmd_path_lst);
}
