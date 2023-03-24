/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:35:15 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/24 22:35:16 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_fix_args(char **cmd_arg)
{
	char	*str;
	char	**strf;

	str = ft_first_clean(cmd_arg);
	if (ft_verify_args(str) != 0)
		return (NULL);
	strf = ft_split(str, '/');
	free(str);
	return (strf);
}

char	*ft_first_clean(char **cmd_arg)
{
	int		i;
	int		j;
	char	*str;
	char	*temp;

	i = 1;
	j = 0;
	str = ft_strdup("");
	while (cmd_arg[i] != NULL)
	{
		while (cmd_arg[i][j] != '\0')
		{
			temp = ft_char_to_str(cmd_arg[i][j++]);
			str = ft_join_free(str, temp);
			free(temp);
		}
		if (cmd_arg[i][j - 1] == 92)
			str = ft_join_free(str, " ");
		else
			break ;
		i++;
		j = 0;
	}
	str = ft_last_clean(str);
	return (str);
}

int	ft_relative_path(t_mini *minishell, char **cmd_arg, char *arg)
{
	int		i;
	char	*path;

	i = 0;
	while (cmd_arg[i] != NULL)
	{
		if (cmd_arg[0] != NULL && cmd_arg[0][0] == '-')
			return (ft_handle_hyphen(minishell));
		if (cmd_arg[i] != NULL && cmd_arg[i][0] == '.' && cmd_arg[i][1] == '.')
			if (ft_handle_operator(minishell, cmd_arg[i], arg) != 0)
				return (1);
		if (cmd_arg[i] != NULL && cmd_arg[i][0] != '.' && cmd_arg[i][1] != '.')
		{
			path = ft_strjoin(minishell->mini_tools->pwd, "/");
			path = ft_join_free(path, cmd_arg[i]);
			if (ft_verify_failure(path, arg, chdir(path)) != 0)
				return (free(path), 1);
			free(path);
			ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
			if (ft_update_pwd(minishell, getcwd(NULL, 1)) != 0)
				return (printf("minishell: cd: an error occured\n"));
		}
		i++;
	}
	return (0);
}

int	ft_absolute_path(t_mini *minishell, char **cmd_arg, char *arg)
{
	int		i;
	char	*path;

	if (arg[0] == '/' && arg[1] == '/' && arg[2] == '\0')
		path = ft_strdup("//");
	else
		path = ft_strdup("/");
	i = chdir(path);
	if (access(path, F_OK) == -1)
		return (printf("minishell: cd: %s: No such file or directory\n", path));
	if (access(path, X_OK) == -1)
		return (printf("minishell: cd: %s: Permission denied\n", path));
	if (i != 0)
		return (printf("minishell: cd: an error occured\n"));
	ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
	ft_update_pwd(minishell, path);
	if (cmd_arg[0] == NULL)
		return (0);
	else
		if (ft_relative_path(minishell, cmd_arg, arg) != 0)
			return (1);
	return (0);
}

int	ft_cd_builtins(char **cmd_arg, t_mini *minishell)
{
	int		i;
	int		absolute;
	char	**str;
	char	*arg;

	absolute = 0;
	arg = ft_first_clean(cmd_arg);
	if (cmd_arg[1] != NULL && cmd_arg[1][0] == '/')
		absolute++;
	if (cmd_arg[1] == NULL)
		i = ft_handle_operator(minishell, cmd_arg[1], arg);
	else
	{
		str = ft_fix_args(cmd_arg);
		if (str == NULL)
			return (1);
		if (str[0] == NULL || absolute != 0)
			i = ft_absolute_path(minishell, str, arg);
		else
			i = ft_relative_path(minishell, str, arg);
		pls_free(str);
	}
	if (i != 0)
		return (free(arg), 1);
	return (free(arg), 0);
}
