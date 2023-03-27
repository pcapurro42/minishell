/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   except_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:36:12 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/24 22:36:13 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_handle_hyphen(t_mini *minishell)
{
	int		i;
	char	*path;

	if (ft_get_variable_again(minishell, 3) == NULL)
		return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	path = ft_get_variable_again(minishell, 3);
	i = chdir(path);
	if (i != 0)
		return (ft_putstr_fd("minishell: cd: an error occured\n", 2), 1);
	ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
	if (ft_update_pwd(minishell, getcwd(NULL, 1)) != 0)
		return (ft_putstr_fd("minishell: cd: an error occured\n", 2), 1);
	ft_putstr_fd(minishell->mini_tools->pwd, 1);
	return (0);
}

int	ft_handle_point_point(t_mini *minishell, char *arg)
{
	int		i;
	char	*path;
	char	*temp;

	path = ft_step_back(minishell->mini_tools->pwd);
	if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
	{
		free(path);
		return (ft_printf_error("minishell: cd: %s/: Permission denied\n", arg));
	}
	while (access(path, F_OK) != 0)
	{
		temp = ft_strdup(path);
		free(path);
		path = ft_step_back(temp);
		free(temp);
	}
	i = chdir(path);
	if (ft_verify_failure(path, arg, i) != 0)
		return (1);
	free(path);
	ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
	if (ft_update_pwd(minishell, getcwd(NULL, 1)) != 0)
		return (ft_putstr_fd("minishell: cd: an error occured\n", 2), 1);
	return (0);
}

int	ft_handle_operator(t_mini *minishell, char *str, char *arg)
{
	int		i;
	char	*path;

	if (str == NULL)
	{
		path = ft_get_variable_again(minishell, 1);
		if (path == NULL)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		i = chdir(path);
		if (ft_verify_failure(path, arg, i) != 0)
			return (1);
		ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
		if (ft_update_pwd(minishell, getcwd(NULL, 1)) != 0)
			return (ft_putstr_fd("minishell: cd: an error occured\n", 2), 1);
	}
	else
	{
		if (ft_strlen(str) == 2)
		{
			if (str[0] == '.' && str[1] == '.' && \
				ft_strlen(minishell->mini_tools->pwd) > 1)
				return (ft_handle_point_point(minishell, arg));
		}
	}
	return (0);
}
