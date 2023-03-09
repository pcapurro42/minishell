/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:31:47 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/07 20:31:47 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verify(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 0)
		{
			if (str[i] == '#' || str[i] == '&' || str[i] == '_' || str[i] == '*')
				return (1);
			else
				return (printf("minishell: unset: '%c': not a valid identifier!\n", str[i]));
		}
		i++;
	}
	return (0);
}

// # et & = ne rien faire
// _ = ne rien faire
// * = ne rien faire
// TOUT LE RESTE QUI N'EST PAS UNE LETTRE = message d'erreur


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

void	ft_unset_builtins(t_mini *minishell, char **cmd_arg)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (cmd_arg[i] != NULL && ft_verify(cmd_arg[i]) == 0)
	{
		cmd_arg[i] = ft_strjoin(cmd_arg[i], "=");
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
	minishell->mini_tools->envp = ft_clean_env(minishell->mini_tools->envp);
}
