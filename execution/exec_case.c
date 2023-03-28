/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:43:12 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/28 18:46:31 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_exec_case2(char **cmd_arg, char **envp, int i)
{
	int		cmd_arg_len;
	char	**tab;

	if (ft_strchr(&(cmd_arg[0][i]), '.'))
	{
		cmd_arg_len = 0;
		while (cmd_arg[cmd_arg_len])
			cmd_arg_len++;
		tab = malloc(sizeof(*tab) * (cmd_arg_len + 2));
		ft_check_malloc(tab);
		cmd_arg_len = 1;
		tab[0] = "/bin/bash";
		tab[1] = &(cmd_arg[0][i]);
		while (cmd_arg[cmd_arg_len])
		{
			tab[cmd_arg_len + 1] = cmd_arg[cmd_arg_len];
			cmd_arg_len++;
		}
		tab[cmd_arg_len + 1] = NULL;
		execve(tab[0], tab, envp);
	}
	else
		execve(cmd_arg[0], cmd_arg, envp);
	ft_error_msg(cmd_arg[0]);
}

void	ft_exec_case(char **cmd_arg, char **envp)
{
	int		i;
	DIR		*directory;
	char	*error_msg;

	if (access(cmd_arg[0], F_OK) != 0)
	{
		error_msg = ft_strjoin("minishell: ", cmd_arg[0]);
		perror(error_msg);
		exit(127);
	}
	if (access(cmd_arg[0], X_OK) != 0)
	{
		error_msg = ft_strjoin("minishell: ", cmd_arg[0]);
		perror(error_msg);
		exit(126);
	}
	i = 0;
	while (ft_strlen((&cmd_arg[0][i])) > 1 && cmd_arg[0][i] == '.' \
	&& cmd_arg[0][i + 1] == '/')
		i += 2;
	directory = opendir(&(cmd_arg[0][i]));
	if (directory == NULL)
		ft_exec_case2(cmd_arg, envp, i);
	closedir(directory);
	ft_error_dir(cmd_arg[0]);
}
