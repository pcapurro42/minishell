/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:52:55 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/16 22:59:04 by vdelafos         ###   ########.fr       */
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

	cmd_path_lst = malloc(6 * sizeof(*cmd_path_lst));
	if (cmd_path_lst == NULL)
		ft_error();
	cmd_path_lst[0] = ft_strdup("/usr/gnu/bin/");
	ft_check_malloc(cmd_path_lst[0]);
	cmd_path_lst[1] = ft_strdup("/usr/local/bin/");
	ft_check_malloc(cmd_path_lst[1]);
	cmd_path_lst[2] = ft_strdup("/bin/");
	ft_check_malloc(cmd_path_lst[2]);
	cmd_path_lst[3] = ft_strdup("/usr/bin/");
	ft_check_malloc(cmd_path_lst[3]);
	cmd_path_lst[4] = ft_strdup("./");
	ft_check_malloc(cmd_path_lst[4]);
	cmd_path_lst[5] = NULL;
	return (cmd_path_lst);
}

static char	**ft_no_path(void)
{
	char	**cmd_path_lst;

	cmd_path_lst = malloc(sizeof(*cmd_path_lst));
	if (cmd_path_lst == NULL)
		ft_error();
	cmd_path_lst[0] = NULL;
	return (cmd_path_lst);
}

char	**ft_find_path(char *envp[], int path_unset)
{
	char	**cmd_path_lst;
	int		i;

	i = 0;
	if (path_unset == 1)
		return (ft_no_path());
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
	ft_check_malloc(cmd_path_lst);
	ft_complete_path(cmd_path_lst);
	return (cmd_path_lst);
}
