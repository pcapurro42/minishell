/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:42 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/16 23:02:43 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_verify_errors_export(char *str)
{
	int		i;
	char	*name_str;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
		name_str = ft_strdup(str);
	i = 0;
	if ((name_str[i] == '#' || name_str[i] == '&' || \
	name_str[i] == '_' || name_str[i] == '*') && name_str[1] == '\0')
	{
		free(name_str);
		return (1);
	}
	while (name_str[i] != '=' && name_str[i] != '\0')
	{
		if ((ft_isalpha(name_str[i]) == 0 && \
		ft_isdigit(name_str[i]) == 0) && name_str[i] != '_')
		{
			free(name_str);
			return (1);
		}
		i++;
	}
	free(name_str);
	return (0);
}

static int	ft_verify_characters_export(char *str)
{
	int		i;
	char	*name_str;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
		name_str = ft_strdup(str);
	i = 0;
	if ((name_str[i] == '#' || name_str[i] == '&' || \
	name_str[i] == '_' || name_str[i] == '*') && name_str[1] == '\0')
	{
		free(name_str);
		return (1);
	}
	while (name_str[i] != '=' && name_str[i] != '\0')
	{
		if ((ft_isalpha(name_str[i]) == 0 && \
		ft_isdigit(name_str[i]) == 0) && name_str[i] != '_')
		{
			free(name_str);
			return (printf("minishell: export: '%s': \
not a valid identifier\n", str));
		}
		i++;
	}
	free(name_str);
	return (0);
}

static int	ft_name_in_envp(char *str, char **envp)
{
	char	*name_str;
	char	*name_envp;
	int		i;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
		name_str = ft_strdup(str);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr_i(envp[i], '=') != -1)
		{
			name_envp = malloc(sizeof(*name_envp) * \
			(ft_strchr_i(envp[i], '=') + 1));
			ft_strlcpy(name_envp, envp[i], ft_strchr_i(envp[i], '=') + 1);
		}
		else
			name_envp = ft_strdup(envp[i]);
		if (ft_strncmp(name_str, name_envp, ft_strlen(name_str) + 1) == 0)
		{
			free(name_str);
			free(name_envp);
			return (0);
		}
		free(name_envp);
		i++;
	}
	free(name_str);
	return (1);
}

static void	ft_replace_in_envp(char *str, char **envp)
{
	char	*name_str;
	char	*name_envp;
	int		i;

	if (ft_strchr_i(str, '=') != -1)
	{
		name_str = malloc(sizeof(*name_str) * (ft_strchr_i(str, '=') + 1));
		ft_strlcpy(name_str, str, ft_strchr_i(str, '=') + 1);
	}
	else
		name_str = ft_strdup(str);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr_i(envp[i], '=') != -1)
		{
			name_envp = malloc(sizeof(*name_envp) * \
			(ft_strchr_i(envp[i], '=') + 1));
			ft_strlcpy(name_envp, envp[i], ft_strchr_i(envp[i], '=') + 1);
		}
		else
			name_envp = ft_strdup(envp[i]);
		if (ft_strncmp(name_str, name_envp, ft_strlen(name_str) + 1) == 0)
		{
			free(name_str);
			free(name_envp);
			free(envp[i]);
			envp[i] = ft_strdup(str);
			ft_check_malloc(envp[i]);
			return ;
		}
		free(name_envp);
		i++;
	}
	free(name_str);
}

void	ft_export_no_arg_builtins(char **envp)
{
	int	i;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(envp[i], '='))
		{
			write(1, envp[i], ft_strchr_i(envp[i], '=') + 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(&(envp[i][ft_strchr_i(envp[i], '=') + 1]), 1);
			ft_putchar_fd('\"', 1);
		}
		else
			ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return ;
}

int	ft_export_builtins(char **cmd_arg, t_mini *minishell)
{
	char	**new_envp;
	int		return_code;
	int		envp_len;
	int		nb_export;
	int		i;

	return_code = 0;
	nb_export = 0;
	i = 0;
	while (cmd_arg[i + 1])
	{
		if (ft_verify_characters_export(cmd_arg[i + 1]) == 0 && \
		ft_name_in_envp(cmd_arg[i + 1], minishell->mini_tools->envp) == 1)
			nb_export++;
		i++;
	}
	if (i == 0)
	{
		ft_export_no_arg_builtins(minishell->mini_tools->envp);
		return (0);
	}
	envp_len = 0;
	while (minishell->mini_tools->envp[envp_len])
		envp_len++;
	new_envp = malloc(sizeof(*new_envp) * (envp_len + nb_export + 1));
	envp_len = 0;
	while (minishell->mini_tools->envp[envp_len])
	{
		new_envp[envp_len] = minishell->mini_tools->envp[envp_len];
		envp_len++;
	}
	i = 0;
	nb_export = 0;
	while (cmd_arg[i + 1])
	{
		if (ft_verify_errors_export(cmd_arg[i + 1]) == 0)
		{
			if (ft_name_in_envp(cmd_arg[i + 1], \
			minishell->mini_tools->envp) == 1)
			{
				if (ft_strncmp(cmd_arg[i + 1], "PATH=", \
				ft_strlen("PATH=")) == 0)
					minishell->mini_tools->path_unset = 0;
				new_envp[envp_len + nb_export] = ft_strdup(cmd_arg[i + 1]);
				nb_export++;
			}
			else
				ft_replace_in_envp(cmd_arg[i + 1], new_envp);
		}
		else
			return_code = 1;
		i++;
	}
	new_envp[envp_len + nb_export] = NULL;
	free(minishell->mini_tools->envp);
	minishell->mini_tools->envp = new_envp;
	return (return_code);
}

// modif variable