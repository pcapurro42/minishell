/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:42 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/20 16:56:29 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_name_in_envp_2(char *name_str, char **envp, int *i)
{	
	char	*name_envp;

	while (envp[*i])
	{
		if (ft_strchr_i(envp[*i], '=') != -1)
		{
			name_envp = malloc(sizeof(*name_envp) * \
			(ft_strchr_i(envp[*i], '=') + 1));
			ft_check_malloc(name_envp);
			ft_strlcpy(name_envp, envp[*i], ft_strchr_i(envp[*i], '=') + 1);
		}
		else
		{
			name_envp = ft_strdup(envp[*i]);
			ft_check_malloc(name_envp);
		}
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

int	ft_name_in_envp(char *str, char **envp)
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
	{
		name_str = ft_strdup(str);
		ft_check_malloc(name_str);
	}
	i = 0;
	if (ft_name_in_envp_2(name_str, envp, &i) == 0)
	{
		free(name_str);
		return (0);
	}
	free(name_str);
	return (1);
}

static char	*ft_create_name_envp(char **envp, int i)
{
	char	*name_envp;

	if (ft_strchr_i(envp[i], '=') != -1)
	{
		name_envp = malloc(sizeof(*name_envp) * \
		(ft_strchr_i(envp[i], '=') + 1));
		ft_check_malloc(name_envp);
		ft_strlcpy(name_envp, envp[i], ft_strchr_i(envp[i], '=') + 1);
	}
	else
	{
		name_envp = ft_strdup(envp[i]);
		ft_check_malloc(name_envp);
	}
	return (name_envp);
}

static void	ft_replace_in_envp_2(char *str, char *name_str, char **envp)
{
	char	*name_envp;
	int		i;

	i = 0;
	while (envp[i])
	{
		name_envp = ft_create_name_envp(envp, i);
		if (ft_strncmp(name_str, name_envp, ft_strlen(name_str) + 1) == 0)
		{
			free(name_envp);
			free(envp[i]);
			envp[i] = ft_strdup(str);
			ft_check_malloc(envp[i]);
			return ;
		}
		free(name_envp);
		i++;
	}
	return ;
}

void	ft_replace_in_envp(char *str, char **envp)
{
	char	*name_str;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_check_malloc(name_str);
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
	{
		name_str = ft_strdup(str);
		ft_check_malloc(name_str);
	}
	ft_replace_in_envp_2(str, name_str, envp);
	free(name_str);
}
