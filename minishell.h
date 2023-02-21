/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:08 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/20 11:00:53 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int	g_last_return_code = 0;

typedef struct s_mini
{
	int		infile;
	int		outfile;
	int		append_mod;

	char	**envp;
	char	**cmd_path_lst;

	char	***cmd_lst;
}	t_mini;

// - EXECUTION - //

// - PARSING - //

#endif
