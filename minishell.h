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

int	g_last_return_code;

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

// - MAIN - //

char	*ft_get_name(void);

// - EXECUTION - //

// - PARSING - //

char	*ft_clean_input(char *input);
char	*ft_add_spaces(char *str);

int		ft_syntax_checker(char *str);
int		ft_empty_checker(char *str);
int		ft_quote_checker(char *str);
int		ft_pipe_chevron_checker(char *str);

int		ft_check_commands(char **str);

char	*ft_analyze_input(char *input);

#endif
