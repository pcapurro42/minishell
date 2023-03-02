/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:27:46 by vdelafos          #+#    #+#             */
/*   Updated: 2023/03/02 17:31:42 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_cpy_envp(char *envp[])
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
	return (envp_cpy);
}
