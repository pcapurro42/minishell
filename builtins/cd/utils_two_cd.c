/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:39:10 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/24 22:39:11 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_verify_failure(char *path, char *arg, int i)
{
	if (access(path, F_OK) == -1)
		return (printf("minishell: cd: %s: No such file or directory\n", arg));
	if (access(path, X_OK) == -1)
		return (printf("minishell: cd: %s: Permission denied\n", arg));
	if (i != 0)
		return (printf("minishell: cd: an error occured\n"));
	return (0);
}

int	ft_verify_args(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			if (i == 0 && str[i + 1] != '\0')
				return (printf("minishell: cd: -: invalid option\n"));
		}
		i++;
	}
	return (0);
}
