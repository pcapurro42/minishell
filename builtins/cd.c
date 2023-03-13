/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 20:31:44 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/13 04:26:06 by vdelafos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_builtins(char **cmd_arg, t_mini *minishell)
{
	(void) cmd_arg;
	(void) minishell;

	printf("C'est pour bientôt...\n");
	return (0);
}

// FONCTIONS À UTILISER :
// - access (!)
// => F_OK, R_OK
// - chdir (!)
// - getcwd (?)
// - opendir (?)
// - readdir (?)
// - closedir (?)