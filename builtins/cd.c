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

	i = 0;
	strf = ft_strdup("");
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
			strf = ft_strjoin(strf, ft_char_to_str(str[i]));
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

static char	**ft_fix_args(char **cmd_arg)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	j = 0;
	str = ft_strdup("");
	while (cmd_arg[i] != NULL)
	{
		while (cmd_arg[i][j] != '\0')
			str = ft_strjoin(str, ft_char_to_str(cmd_arg[i][j++]));
		if (cmd_arg[i][j - 1] == 92)
			str = ft_strjoin(str, " ");
		else
			break ;
		i++;
		j = 0;
	}
	str = ft_last_clean(str);
	if (ft_verify_args(str) != 0)
		return (NULL);
	return (ft_split(str, '/'));
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
	while (minishell->mini_tools->envp[i] != NULL)
	{
		if (ft_strncmp(str, minishell->mini_tools->envp[i], ft_strlen(str)) == 0)
			return (minishell->mini_tools->envp[i] + ft_strlen(str));
		i++;
	}
	return (NULL);
}

static int	ft_update_oldpwd(t_mini *minishell, char *path)
{
	int	i;

	i = 0;
	while (minishell->mini_tools->envp[i] != NULL)
	{
		if (ft_strncmp("OLDPWD=", minishell->mini_tools->envp[i], 7) == 0)
		{
			minishell->mini_tools->envp[i] = ft_strdup("OLDPWD=");
			minishell->mini_tools->envp[i] = ft_strjoin(minishell->mini_tools->envp[i], path);
			minishell->mini_tools->old_pwd = ft_strdup(path);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_update_pwd(t_mini *minishell, char *path)
{
	int	i;

	i = 0;
	while (minishell->mini_tools->envp[i] != NULL)
	{
		if (ft_strncmp("PWD=", minishell->mini_tools->envp[i], 4) == 0)
		{
			minishell->mini_tools->envp[i] = ft_strdup("PWD=");
			minishell->mini_tools->envp[i] = ft_strjoin(minishell->mini_tools->envp[i], path);
			minishell->mini_tools->pwd = ft_strdup(path);
			return (0);
		}
		i++;
	}
	return (1);
}

// static char	*ft_get_end_of_path(char *str)
// {
// 	int	i;

// 	i = ft_strlen(str) - 1;
// 	while (i != 0 && str[i] != '/')
// 		i--;
// 	return (str + i + 1);
// }

static char	*ft_step_back(char *str)
{
	int		i;
	char	*strf;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) - 1;
	strf = ft_strdup("");
	while (i != 0 && str[i] != '/')
	{
		str[i] = -1;
		i--;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != -1)
			strf = ft_strjoin(strf, ft_char_to_str(str[i]));
		i++;
	}
	free(str);
	return (strf);
}

static int	ft_handle_operator(t_mini *minishell, char *str)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (str == NULL || str[0] == '~')
	{
		path = ft_get_variable_again(minishell, 1);
		if (path == NULL)
			return (printf("minishell: cd: HOME not set\n"));
		i = chdir(path);
		if (access(path, F_OK) == -1)
			return (printf("minishell: cd: /: No such file or directory\n"));
		if (access(path, X_OK) == -1)
			return (printf("minishell: cd: /: Permission denied\n"));
		if (i != 0)
			return (printf("minishell: cd: an error occured\n"));
		ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
		ft_update_pwd(minishell, getcwd(NULL, 1));
	}
	else
	{
		if (ft_strlen(str) == 1)
		{
			// if (str[0] == '~')
			// {
			// 	path = ft_strdup(minishell->mini_tools->home_directory);
			// 	i = chdir(path);
			// 	if (access(path, F_OK) == -1)
			// 		return (printf("minishell: cd: /: No such file or directory\n"));
			// 	if (access(path, X_OK) == -1)
			// 		return (printf("minishell: cd: /: Permission denied\n"));
			//  if (i != 0)
			//		return (printf("minishell: cd: an error occured\n"));
			// 	ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
			// 	ft_update_pwd(minishell, getcwd(NULL, 1));
			// }
			if (str[0] == '-')
			{
				if (ft_get_variable_again(minishell, 3) == NULL)
					return (printf("minishell: cd: OLDPWD not set\n"));
				path = ft_get_variable_again(minishell, 3);
				i = chdir(path);
				if (access(path, F_OK) == -1)
					return (printf("minishell: cd: /: No such file or directory\n"));
				if (access(path, X_OK) == -1)
					return (printf("minishell: cd: /: Permission denied\n"));
				if (i != 0)
					return (printf("minishell: cd: an error occured\n"));
				ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
				ft_update_pwd(minishell, getcwd(NULL, 1));
				printf("%s\n", minishell->mini_tools->pwd);
			}
		}
		if (ft_strlen(str) == 2)
		{
			if (str[0] == '.' && str[1] == '.' && ft_strlen(minishell->mini_tools->pwd) > 1)
			{
				path = ft_step_back(minishell->mini_tools->pwd);
				i = chdir(path);
				if (access(path, F_OK) == -1)
					return (printf("minishell: cd: /: No such file or directory\n"));
				if (access(path, X_OK) == -1)
					return (printf("minishell: cd: /: Permission denied\n"));
				if (i != 0)
					return (printf("minishell: cd: an error occured\n"));
				ft_update_oldpwd(minishell, ft_get_variable_again(minishell, 2));
				ft_update_pwd(minishell, getcwd(NULL, 1));
			}
		}
	}
	return (0);
}

static int	ft_handle_relative_path(t_mini *minishell, char **cmd_arg)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (cmd_arg[i] != NULL)
	{
		if (ft_is_operator(cmd_arg[i]) == 1)
			ft_handle_operator(minishell, cmd_arg[i]);
		else
		{
			path = ft_strjoin(minishell->mini_tools->pwd, "/");
			path = ft_strjoin(path, cmd_arg[i]);
			j = chdir(path);
			if (access(path, F_OK) == -1)
				return (printf("minishell: cd: /: No such file or directory\n"));
			if (access(path, X_OK) == -1)
				return (printf("minishell: cd: /: Permission denied\n"));
			if (j != 0)
				return (printf("minishell: cd: an error occured\n"));
			ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
			ft_update_pwd(minishell, getcwd(NULL, 1));
			free(path);
		}
		i++;
	}
	return (0);
}

// minishell: cd: %s/: Permission denied\n
// minishell: cd: %s/: No such file or directory\n

static int	ft_handle_absolute_path(t_mini *minishell, char **cmd_arg)
{
	int	i;

	i = chdir("/");
	if (access("/", F_OK) == -1)
		return (printf("minishell: cd: /: No such file or directory\n"));
	if (access("/", X_OK) == -1)
		return (printf("minishell: cd: /: Permission denied\n"));
	if (i != 0)
		return (printf("minishell: cd: an error occured\n"));
	ft_update_oldpwd(minishell, minishell->mini_tools->pwd);
	ft_update_pwd(minishell, getcwd(NULL, 1));
	if (cmd_arg[0] == NULL)
		return (0);
	else
		ft_handle_relative_path(minishell, cmd_arg);
	return (0);
}

int	ft_cd_builtins(char **cmd_arg, t_mini *minishell)
{
	int		i;
	int		absolute;

	i = 0;
	absolute = 0;
	if (cmd_arg[1] != NULL && cmd_arg[1][0] == '/')
		absolute++;
	if (cmd_arg[1] == NULL)
		i = ft_handle_operator(minishell, cmd_arg[1]);
	else
	{
		cmd_arg = ft_fix_args(cmd_arg);
		if (cmd_arg == NULL)
			return (1);
		if (cmd_arg[0] == NULL || absolute != 0)
			i = ft_handle_absolute_path(minishell, cmd_arg);
		else
			i = ft_handle_relative_path(minishell, cmd_arg);
	}
	if (i != 0)
		return (1);
	return (0);
}

// FONCTIONS À UTILISER :
//
// - chdir (= change et vérifie les DOSSIERS)
// - getcwd (= obtenir le répertoire courant)
// - opendir (= vérifie l'accès au RÉPERTOIRE)
// - closedir (= ferme un répertoire ouvert par opendir j'imagine)

// PROBLÈMES À FIX :
//
// - peauffiner les cas ou on navigue dans un directory qui n'existe plus
// - ...

// CAS À GÉRER :
//
// - "-" (= aller dans le répertoire ou l'on se trouvait avant)
// - "." (= ne fait rien...)
// - ".." (= recule de un)
// - " " (= redirige sur $HOME)
// - "~" (= redirige sur $HOME sans passer par $HOME)