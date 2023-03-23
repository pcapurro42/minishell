/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:27:46 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/16 22:57:13 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_getpwd_i(int *i)
{
	char	*buf;
	char	*ret;

	ret = NULL;
	while (ret == NULL)
	{
		buf = malloc(sizeof(*buf) * (*i + 1));
		ft_check_malloc(buf);
		ret = getcwd(buf, *i);
		(*i)++;
		if (ret == NULL)
			free(buf);
	}
	return (buf);
}

char	*ft_getpwd(void)
{
	char	*buf;
	char	*pwd;
	int		i;

	i = 1;
	buf = ft_getpwd_i(&i);
	pwd = malloc(sizeof(*buf) * (i + 4));
	ft_check_malloc(pwd);
	pwd[0] = 'P';
	pwd[1] = 'W';
	pwd[2] = 'D';
	pwd[3] = '=';
	i = 0;
	while (buf[i])
	{
		pwd[i + 4] = buf[i];
		i++;
	}
	pwd[i + 4] = '\0';
	free(buf);
	return (pwd);
}

char	*ft_getshlvl(void)
{
	char	*shlvl;

	shlvl = ft_strdup("SHLVL=0");
	return (shlvl);
}

char	*ft_get_(char	*pwd, char	*exec_name)
{
	char	*temp;
	char	*temp2;
	char	*_;

	temp = ft_strjoin("_", &(pwd[3]));
	temp2 = ft_strjoin(temp, "/");
	_ = ft_strjoin(temp2, exec_name);
	free(pwd);
	free(temp);
	free(temp2);
	return (_);
}

char	*ft_gethome(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	home = ft_strdup(&(envp[i][5]));
	return (home);
}
