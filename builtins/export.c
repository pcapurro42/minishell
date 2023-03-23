/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:42 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/20 16:56:31 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_no_arg_builtins(char **envp)
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

static int	ft_export_builtins_nb_export(char **cmd_arg, t_mini *minishell)
{
	int		nb_export;
	int		i;

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
	return (i);
}

static void	ft_export_builtins_3(char **cmd_arg, t_mini *minishell, \
t_export *export_nb, char **new_envp)
{
	if (ft_strncmp(cmd_arg[export_nb->i + 1], "PATH=", \
	ft_strlen("PATH=")) == 0)
		minishell->mini_tools->path_unset = 0;
	new_envp[export_nb->envp_len + export_nb->nb_export] = \
	ft_strdup(cmd_arg[export_nb->i + 1]);
	export_nb->nb_export++;
}

static void	ft_export_builtins_2(char **cmd_arg, t_mini *minishell, \
char **new_envp, t_export *export_nb)
{
	export_nb->return_code = 0;
	export_nb->nb_export = 0;
	export_nb->i = 0;
	while (cmd_arg[export_nb->i + 1])
	{
		if (ft_verify_errors_export(cmd_arg[export_nb->i + 1]) == 0)
		{
			if (ft_name_in_envp(cmd_arg[export_nb->i + 1], \
			minishell->mini_tools->envp) == 1)
				ft_export_builtins_3(cmd_arg, minishell, export_nb, new_envp);
			else
				ft_replace_in_envp(cmd_arg[export_nb->i + 1], new_envp);
		}
		else
			export_nb->return_code = 1;
		export_nb->i++;
	}
	new_envp[export_nb->envp_len + export_nb->nb_export] = NULL;
}

int	ft_export_builtins(char **cmd_arg, t_mini *minishell)
{
	char		**new_envp;
	t_export	*export_nb;

	export_nb = malloc(sizeof(*export_nb));
	ft_check_malloc(export_nb);
	export_nb->nb_export = ft_export_builtins_nb_export(cmd_arg, minishell);
	if (export_nb->nb_export == 0)
		return (free(export_nb), 0);
	export_nb->envp_len = 0;
	while (minishell->mini_tools->envp[export_nb->envp_len])
		export_nb->envp_len++;
	new_envp = malloc(sizeof(*new_envp) * (export_nb->envp_len + \
	export_nb->nb_export + 1));
	ft_check_malloc(new_envp);
	export_nb->envp_len = 0;
	while (minishell->mini_tools->envp[export_nb->envp_len])
	{
		new_envp[export_nb->envp_len] = \
		minishell->mini_tools->envp[export_nb->envp_len];
		export_nb->envp_len++;
	}
	ft_export_builtins_2(cmd_arg, minishell, new_envp, export_nb);
	free(minishell->mini_tools->envp);
	minishell->mini_tools->envp = new_envp;
	return (free(export_nb), export_nb->return_code);
}
