/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:27:46 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/14 09:39:04 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_find_line_env(char **envp, char *name)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_find_line_env_nb(char **envp, char *name)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_getpwd(void)
{
	char	*buf;
	char	*ret;
	char	*pwd;
	int 	i;

	ret = NULL;
	i = 1;
	while (ret == NULL)
	{
		buf = malloc(sizeof(*buf) * (i + 1));
		ft_check_malloc(buf);
		ret = getcwd(buf, i);
		i++;
		if (ret == NULL)
			free(buf);
	}
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

static char	*ft_getshlvl()
{
	char	*shlvl;

	shlvl = ft_strdup("SHLVL=0");
	ft_check_malloc(shlvl);
	return (shlvl);

}

static void	ft_increase_shlvl(char	**envp)
{
	int 	i_shlvl;
	int		nb_shlvl;
	char	*nb_str_shlvl;
	char	*shlvl_line;

	i_shlvl = ft_find_line_env_nb(envp, "SHLVL=");
	nb_shlvl = ft_atoi(&(envp[i_shlvl][6]));
	nb_str_shlvl = ft_itoa(nb_shlvl + 1);
	ft_check_malloc(nb_str_shlvl);
	shlvl_line = ft_strjoin("SHLVL=", nb_str_shlvl);
	free(envp[i_shlvl]);
	free(nb_str_shlvl);
	envp[i_shlvl] = shlvl_line;
}

static char	*ft_get_(char	*pwd, char	*exec_name)
{
	char	*temp;
	char	*temp2;
	char	*_;

	temp = ft_strjoin("_", &(pwd[3]));
	ft_check_malloc(temp);
	temp2 = ft_strjoin(temp, "/");
	ft_check_malloc(temp2);
	_ = ft_strjoin(temp2, exec_name);
	ft_check_malloc(_);
	free(pwd);
	free(temp);
	free(temp2);
	return (_);
}

static void	ft_check_env(char ***envp, int envp_len, char **argv)
{
	char	**new_envp;
	int		nb_missing_lines;
	int		i;

	nb_missing_lines = ft_find_line_env(*envp, "PWD=") + \
	ft_find_line_env(*envp, "SHLVL=") + ft_find_line_env(*envp, "_=");
	if (nb_missing_lines != 0)
	{
		new_envp = malloc(sizeof(*new_envp) * \
		(nb_missing_lines + envp_len + 1));
		i = 0;
		while ((*envp)[i])
		{
			new_envp[i] = (*envp)[i];
			i++;
		}
		if (ft_find_line_env(*envp, "PWD=") == 1)
			new_envp[i++] = ft_getpwd();
		if (ft_find_line_env(*envp, "SHLVL=") == 1)
			new_envp[i++] = ft_getshlvl();
		if (ft_find_line_env(*envp, "_=") == 1)
			new_envp[i++] = ft_get_(ft_getpwd(), argv[0]);
		new_envp[i] = NULL;
		pls_free(*envp);
		*envp = new_envp;
	}
}

char	**ft_cpy_envp(char *envp[], char **argv)
{
	char	**envp_cpy;
	int		envp_len;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	envp_cpy = malloc(sizeof(*envp) * envp_len + 1);
	envp_len = 0;
	while (envp[envp_len])
	{
		envp_cpy[envp_len] = ft_strdup(envp[envp_len]);
		envp_len++;
	}
	envp_cpy[envp_len] = NULL;
	ft_check_env(&envp_cpy, envp_len, argv);
	ft_increase_shlvl(envp_cpy);
	return (envp_cpy);
}

char	*ft_get_home(char **envp)
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
	ft_check_malloc(home);
	return (home);
}