/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:27:46 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/28 19:44:36 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_line_env(char **envp, char *name)
{
	int	i;

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
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_increase_shlvl(char	**envp)
{
	int		i_shlvl;
	int		nb_shlvl;
	char	*nb_str_shlvl;
	char	*shlvl_line;

	i_shlvl = ft_find_line_env_nb(envp, "SHLVL=");
	nb_shlvl = ft_atoi(&(envp[i_shlvl][6]));
	nb_str_shlvl = ft_itoa(nb_shlvl + 1);
	shlvl_line = ft_strjoin("SHLVL=", nb_str_shlvl);
	free(envp[i_shlvl]);
	free(nb_str_shlvl);
	envp[i_shlvl] = shlvl_line;
}

void	ft_check_env(char ***envp, int envp_len, char **argv)
{
	char	**new_envp;
	int		nb_missing_lines;
	int		i;

	nb_missing_lines = ft_find_nb_missing_lines(*envp);
	if (nb_missing_lines == 0)
		return ;
	new_envp = malloc(sizeof(*new_envp) * \
	(nb_missing_lines + envp_len + 1));
	ft_check_malloc(new_envp);
	i = -1;
	while ((*envp)[++i])
		new_envp[i] = (*envp)[i];
	if (ft_find_line_env(*envp, "PWD=") == 1)
		new_envp[i++] = ft_getpwd();
	if (ft_find_line_env(*envp, "SHLVL=") == 1)
		new_envp[i++] = ft_getshlvl();
	if (ft_find_line_env(*envp, "_=") == 1)
		new_envp[i++] = ft_get_(ft_getpwd(), argv[0]);
	if (ft_find_line_env(*envp, "OLDPWD=") == 1)
		new_envp[i++] = ft_getoldpwd();
	new_envp[i] = NULL;
	free(*envp);
	*envp = new_envp;
}

char	**ft_cpy_envp(char *envp[], char **argv)
{
	char	**envp_cpy;
	int		envp_len;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	envp_cpy = malloc(sizeof(*envp) * envp_len + 1);
	ft_check_malloc(envp_cpy);
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
