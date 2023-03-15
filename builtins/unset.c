/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:31:47 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/13 04:25:34 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verify_errors(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '#' || str[i] == '&' || str[i] == '_' || str[i] == '*') && str[1] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if ((ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_verify_characters(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '#' || str[i] == '&' || str[i] == '_' || str[i] == '*') && str[1] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if ((ft_isalpha(str[i]) == 0 && ft_isdigit(str[i]) == 0) && str[i] != '_')
			return (printf("minishell: unset: '%s': not a valid identifier\n", str));
		i++;
	}
	return (0);
}

static char	**ft_clean_env(char **envp)
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
	i = 0;
	k = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] != -1)
		{
			new_envp[k++] = ft_strdup(envp[i]);
			ft_check_malloc(new_envp[k - 1]);
		}
		i++;
	}
	new_envp[k] = NULL;
	pls_free(envp);
	return (new_envp);
}

int	ft_unset_builtins(t_mini *minishell, char **cmd_arg)
{
	int		i;
	int		j;
	int		return_code;
	char	*temp;

	return_code = 0;
	i = 1;
	j = 0;
	while (cmd_arg[i] != NULL && ft_verify_characters(cmd_arg[i]) == 0)
	{
		temp = ft_strdup(cmd_arg[i]);
		ft_check_malloc(temp);
		free(cmd_arg[i]);
		cmd_arg[i] = ft_strjoin(temp, "=");
		ft_check_malloc(cmd_arg[i]);
		free(temp);
		while (minishell->mini_tools->envp[j] != NULL)
		{
			if (ft_strncmp(cmd_arg[i], minishell->mini_tools->envp[j], ft_strlen(cmd_arg[i])) == 0)
			{
				cmd_arg[i][0] = -1;
				minishell->mini_tools->envp[j][0] = -1;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (cmd_arg[i] != NULL && ft_verify_errors(cmd_arg[i]) != 0)
		return_code = 1;
	minishell->mini_tools->envp = ft_clean_env(minishell->mini_tools->envp);
	return (return_code);
}
