/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:52:55 by vdelafos          #+#    #+#             */
/*   Updated: 2023/02/22 13:42:06 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_complete_path(char **cmd_path_lst)
{
	int		i;
	char	*temp;

	i = 0;
	ft_check_malloc(cmd_path_lst[0]);
	while (cmd_path_lst[i])
	{
		temp = ft_strjoin(cmd_path_lst[i], "/");
		ft_check_malloc(temp);
		free(cmd_path_lst[i]);
		cmd_path_lst[i] = temp;
		i++;
	}
}

char	**ft_no_env(void)
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
	char	*temp;
	int		i;

	i = 0;
	if (!envp || !(envp[0]))
		return (ft_no_env());
	while (ft_strncmp(envp[i], "_=", 2) != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (ft_strncmp(envp[i], "_=", 2) == 0)
		return (ft_no_env());
	cmd_path_lst = ft_split(envp[i], ':');
	if (cmd_path_lst && cmd_path_lst[0])
	{
		temp = ft_strdup(&(cmd_path_lst[0][5]));
		free(cmd_path_lst[0]);
		cmd_path_lst[0] = temp;
	}
	else
		ft_error();
	return (ft_complete_path(cmd_path_lst), cmd_path_lst);
}
