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

# include "libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

int	g_last_return_code = 0;

typedef struct s_mini
{
	int		infile;
	int		outfile;
	int		append_mod;

	char	**envp;
	char	**cmd_path_lst;
	char	**history;

	char	***cmd_lst;
}	t_mini;

// - EXECUTION - //

// - PARSING - //

char	*ft_analyze_input(char *input);
char	*ft_get_name(void);

#endif
