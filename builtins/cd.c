/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:31:44 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/13 04:26:06 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_last_clean(char *str)
{
	int		i;
	char	*strf;
	char	*temp1;
	char	*temp2;

	i = 0;
	strf = ft_strdup("");
	ft_check_malloc(strf);
	while (str[i] != '\0')
	{
		if (str[i] == 92)
			str[i] = -1;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != -1)
		{
			temp1 = ft_strdup(strf);
			ft_check_malloc(temp1);
			free(strf);
			temp2 = ft_char_to_str(str[i]);
			strf = ft_strjoin(temp1, temp2);
			ft_check_malloc(strf);
			free(temp1);
			free(temp2);
		}
		i++;
	}
	free(str);
	return (strf);
}

static int	ft_verify_args(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			if (i == 0 && str[i + 1] != '\0')
				return (printf("minishell: cd: -: invalid option\n"));
		}
		i++;
	}
	return (0);
}

static char	*ft_first_clean(char **cmd_arg)
{
	int		i;
	int		j;
	char	*str;
	char	*temp1;
	char	*temp2;

	i = 1;
	j = 0;
	str = ft_strdup("");
	ft_check_malloc(str);
	while (cmd_arg[i] != NULL)
	{
		while (cmd_arg[i][j] != '\0')
		{
			temp1 = ft_strdup(str);
			ft_check_malloc(temp1);
			free(str);
			temp2 = ft_char_to_str(cmd_arg[i][j++]);
			str = ft_strjoin(temp1, temp2);
			ft_check_malloc(str);
			free(temp1);
			free(temp2);
		}
		if (cmd_arg[i][j - 1] == 92)
		{
			temp1 = ft_strdup(str);
			ft_check_malloc(temp1);
			free(str);
			str = ft_strjoin(temp1, " ");
			ft_check_malloc(str);
			free(temp1);
		}
		else
			break ;
		i++;
		j = 0;
	}
	str = ft_last_clean(str);
	return (str);
}

static char	**ft_fix_args(char **cmd_arg)
{
	char	*str;
	char	**strf;

	str = ft_first_clean(cmd_arg);
	if (ft_verify_args(str) != 0)
		return (NULL);
	strf = ft_split(str, '/');
	ft_check_malloc(strf);
	free(str);
	return (strf);
}

static int	ft_is_operator(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '.')
			return (1);
		if (str[0] == '~')
			return (1);
		if (str[0] == '-')
			return (1);
	}
	if (ft_strlen(str) == 2)
	{
		if (str[0] == '.' && str[1] == '.')
			return (1);
	}
	return (0);
}

static char	*ft_get_variable_again(t_mini *minishell, int a)
{
	int		i;
	char	*str;

	i = 0;
	if (a == 1)
		str = ft_strdup("HOME=");
	if (a == 2)
		str = ft_strdup("PWD=");
	if (a == 3)
		str = ft_strdup("OLDPWD=");
	ft_check_malloc(str);
	while (minishell->mini_tools->envp[i] != NULL)
	{
		if (ft_strncmp(str, minishell->mini_tools->envp[i], ft_strlen(str)) == 0)
			return (free(str), (minishell->mini_tools->envp[i] + ft_strlen(str)));
		i++;
	}
	free(str);
	return (NULL);
}

static int	ft_update_oldpwd(t_mini *minishell, char *path)
{
	int		i;
	char	*temp;

	i = 0;
	while (minishell->mini_tools->envp[i] != NULL)
	{
		if (ft_strncmp("OLDPWD=", minishell->mini_tools->envp[i], 7) == 0)
		{
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strdup("OLDPWD=");
			ft_check_malloc(minishell->mini_tools->envp[i]);
			temp = ft_strdup(minishell->mini_tools->envp[i]);
			ft_check_malloc(temp);
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strjoin(temp, path);
			ft_check_malloc(minishell->mini_tools->envp[i]);
			free(temp);
			free(minishell->mini_tools->old_pwd);
			minishell->mini_tools->old_pwd = ft_strdup(path);
			ft_check_malloc(minishell->mini_tools->envp[i]);
			ft_check_malloc(minishell->mini_tools->old_pwd);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_update_pwd(t_mini *minishell, char *path)
{
	int		i;
	char	*temp;

	i = 0;
	while (minishell->mini_tools->envp[i] != NULL)
	{
		if (ft_strncmp("PWD=", minishell->mini_tools->envp[i], 4) == 0)
		{
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strdup("PWD=");
			ft_check_malloc(minishell->mini_tools->envp[i]);
			temp = ft_strdup(minishell->mini_tools->envp[i]);
			ft_check_malloc(temp);
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strjoin(temp, path);
			ft_check_malloc(minishell->mini_tools->envp[i]);
			free(temp);
			free(minishell->mini_tools->pwd);
			minishell->mini_tools->pwd = ft_strdup(path);
			ft_check_malloc(minishell->mini_tools->envp[i]);
			ft_check_malloc(minishell->mini_tools->pwd);
			free(path);
			return (0);
		}
		i++;
	}
	free(path);
	return (1);
}

static char	*ft_step_back(char *path)
{
	int		i;
	char	*str;
	char	*strf;
	char	*temp1;
	char	*temp2;

	if (path == NULL)
		return (NULL);
	str = ft_strdup(path);
	ft_check_malloc(str);
	i = ft_strlen(str);
	strf = ft_strdup("");
	ft_check_malloc(strf);
	str[i] = -1;
	while (i != 0 && str[i] != '/')
		str[i--] = -1;
	if (i != 0)
		str[i] = -1;
	i = 0;
	while (str[i] != '\0' && str[i] != -1)
	{
		temp1 = ft_strdup(strf);
		ft_check_malloc(temp1);
		free(strf);
		temp2 = ft_char_to_str(str[i++]);
		strf = ft_strjoin(temp1, temp2);
		ft_check_malloc(strf);
		free(temp1);
		free(temp2);
	}
	free(str);
	return (strf);
}

static int	ft_handle_exception(t_mini *minishell, char *arguments)
{
	int		i;
	char	*path;
	char	*temp;

	if (ft_get_variable_again(minishell, 3) == NULL)
		return (printf("minishell: cd: OLDPWD not set\n"));
	path = ft_get_variable_again(minishell, 3);
	i = chdir(path);
	if (access(path, F_OK) == -1)
		return (printf("minishell: cd: %s: No such file or directory\n", arguments));
	if (access(path, X_OK) == -1)
		return (printf("minishell: cd: %s: Permission denied\n", arguments));
	if (i != 0)
		return (printf("minishell: cd: an error occured\n"));
	ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
	temp = getcwd(NULL, 1);
	if (temp != NULL)
		ft_update_pwd(minishell, temp);
	else
		return (printf("minishell: cd: an error occured\n"));
	printf("%s\n", minishell->mini_tools->pwd);
	return (0);
}

static int	ft_handle_operator(t_mini *minishell, char *str, char *arguments)
{
	int		i;
	char	*path;
	char	*temp;

	if (str == NULL) // cd " "
	{
		path = ft_get_variable_again(minishell, 1);
		if (path == NULL)
			return (printf("minishell: cd: HOME not set\n"));
		i = chdir(path);
		if (access(path, F_OK) == -1)
			return (printf("minishell: cd: %s: No such file or directory\n", arguments));
		if (access(path, X_OK) == -1)
			return (printf("minishell: cd: %s: Permission denied\n", arguments));
		if (i != 0)
			return (printf("minishell: cd: an error occured\n"));
		ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
		temp = getcwd(NULL, 1);
		if (temp != NULL)
			ft_update_pwd(minishell, temp);
		else
			return (printf("minishell: cd: an error occured\n"));
	}
	else
	{
		if (ft_strlen(str) == 2)
		{
			if (str[0] == '.' && str[1] == '.' && ft_strlen(minishell->mini_tools->pwd) > 1) // cd ".."
			{
				path = ft_step_back(minishell->mini_tools->pwd);
				if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
					return (free(path), printf("minishell: cd: %s/: Permission denied\n", arguments));
				while (access(path, F_OK) != 0)
				{
					temp = ft_strdup(path);
					ft_check_malloc(temp);
					free(path);
					path = ft_step_back(temp);
					free(temp);
				}
				i = chdir(path);
				if (access(path, F_OK) == -1)
					return (printf("minishell: cd: %s/: No such file or directory\n", arguments));
				if (access(path, X_OK) == -1)
					return (printf("minishell: cd: %s/: Permission denied\n", arguments));
				if (i != 0)
					return (printf("minishell: cd: an error occured\n"));
				ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
				free(path);
				temp = getcwd(NULL, 1);
				if (temp != NULL)
					ft_update_pwd(minishell, temp);
				else
					return (printf("minishell: cd: an error occured\n"));
			}
		}
	}
	return (0);
}

static int	ft_handle_relative_path(t_mini *minishell, char **cmd_arg, char *arguments)
{
	int		i;
	int		j;
	char	*path;
	char	*temp;

	i = 0;
	while (cmd_arg[i] != NULL)
	{
		if (cmd_arg[0][0] == '-')
			return (ft_handle_exception(minishell, arguments));
		if (ft_is_operator(cmd_arg[i]) == 1 && cmd_arg[i][0] != '~' && cmd_arg[i][0] != '-')
			ft_handle_operator(minishell, cmd_arg[i], arguments);
		else
		{
			path = ft_strjoin(minishell->mini_tools->pwd, "/");
			ft_check_malloc(path);
			temp = ft_strdup(path);
			ft_check_malloc(temp);
			free(path);
			path = ft_strjoin(temp, cmd_arg[i]);
			ft_check_malloc(path);
			free(temp);
			j = chdir(path);
			if (access(path, F_OK) == -1)
				return (free(path), printf("minishell: cd: %s: No such file or directory\n", arguments));
			if (access(path, X_OK) == -1)
				return (free(path), printf("minishell: cd: %s: Permission denied\n", arguments));
			if (j != 0)
				return (free(path), printf("minishell: cd: an error occured\n"));
			free(path);
			ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
			temp = getcwd(NULL, 1);
			if (temp != NULL)
				ft_update_pwd(minishell, temp);
			else
				return (printf("minishell: cd: an error occured\n"));
		}
		i++;
	}
	return (0);
}

static int	ft_handle_absolute_path(t_mini *minishell, char **cmd_arg, char *arguments)
{
	int		i;
	char	*path;
	char	*temp;

	if (cmd_arg != NULL && cmd_arg[0] != NULL && cmd_arg[0][0] == '~') // cd "~"
	{
		path = ft_strdup(minishell->mini_tools->home_directory);
		ft_check_malloc(path);
		i = chdir(path);
		if (access(path, F_OK) == -1)
			return (printf("minishell: cd: %s: No such file or directory\n", arguments));
		if (access(path, X_OK) == -1)
			return (printf("minishell: cd: %s: Permission denied\n", arguments));
		if (i != 0)
			return (printf("minishell: cd: an error occured\n"));
		ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
		temp = getcwd(NULL, 1);
		if (temp != NULL)
			ft_update_pwd(minishell, temp);
		else
			return (printf("minishell: cd: an error occured\n"));
		free(temp);
		ft_handle_relative_path(minishell, cmd_arg + 1, arguments);
	}
	else // cd "/"
	{
		if (arguments[0] == '/' && arguments[1] == '/' && arguments[2] == '\0')
			path = ft_strdup("//");
		else
			path = ft_strdup("/");
		ft_check_malloc(path);
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
			ft_handle_relative_path(minishell, cmd_arg, arguments);
	}
	return (0);
}

int	ft_cd_builtins(char **cmd_arg, t_mini *minishell)
{
	int		i;
	int		absolute;
	char	**str;
	char	*arguments;

	i = 0;
	absolute = 0;
	arguments = ft_first_clean(cmd_arg);
	if (cmd_arg[1] != NULL && ((cmd_arg[1][0] == '/') || (cmd_arg[1][0] == '~' && cmd_arg[1][1] == '\0')))
		absolute++;
	if (cmd_arg[1] == NULL) // cd " "
		i = ft_handle_operator(minishell, cmd_arg[1], arguments);
	else
	{
		str = ft_fix_args(cmd_arg);
		if (str == NULL)
			return (1);
		if (str[0] == NULL || absolute != 0)
			i = ft_handle_absolute_path(minishell, str, arguments);
		else
			i = ft_handle_relative_path(minishell, str, arguments);
		pls_free(str);
	}
	free(arguments);
	if (i != 0)
		return (1);
	return (0);
}
