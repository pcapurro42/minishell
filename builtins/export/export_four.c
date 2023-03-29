/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_four.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:16:55 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/29 11:23:06 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_name_in_cmd_arg_2(char *name_str, char **cmd_arg, int *i, int j)
{
	char	*name_envp;

	while (*i < j)
	{
		if (ft_strchr_i(cmd_arg[*i], '=') != -1)
		{
			name_envp = malloc(sizeof(*name_envp) * \
			(ft_strchr_i(cmd_arg[*i], '=') + 1));
			ft_check_malloc(name_envp);
			ft_strlcpy(name_envp, cmd_arg[*i], ft_strchr_i(cmd_arg[*i], '=') + 1);
		}
		else
			name_envp = ft_strdup(cmd_arg[*i]);
		if (ft_strncmp(name_str, name_envp, ft_strlen(name_str) + 1) == 0)
		{
			free(name_envp);
			return (0);
		}
		free(name_envp);
		(*i)++;
	}
	return (1);
}

int	ft_name_in_cmd_arg(char *str, char **cmd_arg, int j)
{
	char	*name_str;
	int		i;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_check_malloc(name_str);
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
		name_str = ft_strdup(str);
	i = 1;
	if (ft_name_in_cmd_arg_2(name_str, cmd_arg, &i, j) == 0)
	{
		free(name_str);
		return (0);
	}
	free(name_str);
	return (1);
}