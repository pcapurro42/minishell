/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:36:59 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/24 22:37:00 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_last_clean(char *str)
{
	int		i;
	char	*strf;
	char	*temp;

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
		{
			temp = ft_char_to_str(str[i]);
			strf = ft_join_free(strf, temp);
			free(temp);
		}
		i++;
	}
	return (free(str), strf);
}

char	*ft_get_variable_again(t_mini *minishell, int a)
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
		if (ft_strncmp(str, minishell->mini_tools->envp[i], \
			ft_strlen(str)) == 0)
			return (free(str), \
				(minishell->mini_tools->envp[i] + ft_strlen(str)));
		i++;
	}
	free(str);
	return (NULL);
}

int	ft_update_oldpwd(t_mini *minishell, char *path)
{
	int		i;
	char	*temp;
	char	*tmp;

	i = 0;
	while (minishell->mini_tools->envp[i] != NULL)
	{
		tmp = ft_strjoin(minishell->mini_tools->envp[i], "=");
		if (ft_strncmp("OLDPWD=", tmp, 7) == 0)
		{
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strdup("OLDPWD=");
			temp = ft_strdup(minishell->mini_tools->envp[i]);
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strjoin(temp, path);
			free(temp);
			free(minishell->mini_tools->old_pwd);
			minishell->mini_tools->old_pwd = ft_strdup(path);
			return (free(tmp), 0);
		}
		i++;
		free(tmp);
	}
	ft_update_ifnot(path, minishell, 1);
	return (0);
}

int	ft_update_pwd(t_mini *minishell, char *path)
{
	int		i;
	char	*temp;

	i = 0;
	if (path == NULL)
		return (1);
	while (minishell->mini_tools->envp[i] != NULL)
	{
		if (ft_strncmp("PWD=", minishell->mini_tools->envp[i], 4) == 0)
		{
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strdup("PWD=");
			temp = ft_strdup(minishell->mini_tools->envp[i]);
			free(minishell->mini_tools->envp[i]);
			minishell->mini_tools->envp[i] = ft_strjoin(temp, path);
			free(temp);
			free(minishell->mini_tools->pwd);
			minishell->mini_tools->pwd = ft_strdup(path);
			return (free(path), 0);
		}
		i++;
	}
	ft_update_ifnot(path, minishell, 0);
	return (free(path), 0);
}

char	*ft_step_back(char *path)
{
	int		i;
	char	*str;
	char	*strf;
	char	*temp;

	if (path == NULL)
		return (NULL);
	str = ft_strdup(path);
	strf = ft_strdup("");
	i = ft_strlen(str);
	str[i] = -1;
	while (i != 0 && str[i] != '/')
		str[i--] = -1;
	if (i != 0)
		str[i] = -1;
	i = 0;
	while (str[i] != '\0' && str[i] != -1)
	{
		temp = ft_char_to_str(str[i++]);
		strf = ft_join_free(strf, temp);
		free(temp);
	}
	free(str);
	return (strf);
}
