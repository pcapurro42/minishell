/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:39:10 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/24 22:39:11 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_update_ifnot(char *path, t_mini *minishell, int k)
{
	char	**str;

	str = malloc(sizeof(char *) * 2 + 1);
	str[2] = NULL;
	str[0] = ft_strdup("export");
	if (k == 0)
	{
		free(minishell->mini_tools->pwd);
		minishell->mini_tools->pwd = ft_strdup(path);
		str[1] = ft_strdup("PWD=");
	}
	else
	{
		free(minishell->mini_tools->old_pwd);
		minishell->mini_tools->old_pwd = ft_strdup(path);
		str[1] = ft_strdup("OLDPWD=");
	}
	str[1] = ft_join_free(str[1], path);
	ft_export_builtins(str, minishell);
	pls_free(str);
}

int	ft_rp_core(t_mini *minishell, char **cmd_arg, char *arg, int i)
{
	char	*path;

	path = ft_strjoin(minishell->mini_tools->pwd, "/");
	path = ft_join_free(path, cmd_arg[i]);
	if (ft_verify_failure(path, arg, chdir(path)) != 0)
		return (free(path), 1);
	free(path);
	ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
	if (ft_update_pwd(minishell, getcwd(NULL, 1)) != 0)
		return (ft_putstr_fd("minishell: cd: an error occured\n", 2), 1);
	return (0);
}

int	ft_verify_failure(char *path, char *arg, int i)
{
	struct stat	tmp;

	stat(path, &tmp);
	if (access(path, F_OK) == -0 && S_ISDIR(tmp.st_mode) == 0)
	{
		ft_printf_error("minishell: cd: %s: Not a directory\n", arg);
		return (1);
	}
	if (access(path, F_OK) == -1)
	{
		ft_printf_error("minishell: cd: %s: No such file or directory\n", arg);
		return (1);
	}
	if (access(path, X_OK) == -1)
		return (ft_printf_error("minishell: cd: %s: Permission denied\n", arg));
	if (i != 0)
	{
		ft_putstr_fd("minishell: cd: an error occured\n", 2);
		return (1);
	}
	return (0);
}

int	ft_verify_args(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			if (i == 0 && str[i + 1] != '\0')
			{
				ft_putstr_fd("minishell: cd: -: invalid option\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
