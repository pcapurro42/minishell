/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:56:43 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/29 04:56:44 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verify_unset_errors(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '#' || str[i] == '&' || str[i] == '_' \
		|| str[i] == '*') && str[1] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if ((ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0) \
			&& str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_verify_unset_characters(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '#' || str[i] == '&' || str[i] == '_' \
		|| str[i] == '*') && str[1] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if ((ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0) \
			&& str[i] != '_')
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_printf_error("'%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_clean_env(char **envp)
{
	int		i;
	int		k;
	char	**new_envp;

	i = 0;
	k = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] != -1)
			k++;
		i++;
	}
	new_envp = malloc(sizeof(char *) * k + 1);
	ft_check_malloc(new_envp);
	i = 0;
	k = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] != -1)
			new_envp[k++] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[k] = NULL;
	pls_free(envp);
	return (new_envp);
}

void	ft_browse_unit(t_mini *minishell, char **cmd_arg, int i)
{
	int		j;
	char	*temp;

	j = 0;
	while (minishell->mini_tools->envp[j] != NULL)
	{
		temp = ft_strjoin(minishell->mini_tools->envp[j], "=");
		if (ft_strncmp(cmd_arg[i], temp, ft_strlen(cmd_arg[i])) == 0)
		{
			cmd_arg[i][0] = -1;
			minishell->mini_tools->envp[j][0] = -1;
		}
		free(temp);
		j++;
	}
}

int	ft_unset_builtins(t_mini *minishell, char **cmd_arg)
{
	int		i;
	int		return_code;
	char	*temp;

	return_code = 0;
	i = 1;
	while (cmd_arg[i] != NULL && ft_verify_unset_characters(cmd_arg[i]) == 0)
	{
		temp = ft_strdup(cmd_arg[i]);
		free(cmd_arg[i]);
		cmd_arg[i] = ft_strjoin(temp, "=");
		free(temp);
		if (ft_strncmp(cmd_arg[i], "PATH=", ft_strlen(cmd_arg[i])) == 0)
			minishell->mini_tools->path_unset = 1;
		ft_browse_unit(minishell, cmd_arg, i);
		i++;
	}
	if (cmd_arg[i] != NULL && ft_verify_unset_errors(cmd_arg[i]) != 0)
		return_code = 1;
	minishell->mini_tools->envp = ft_clean_env(minishell->mini_tools->envp);
	return (return_code);
}
