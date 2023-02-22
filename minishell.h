/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:08 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/22 13:19:57 by vdelafos         ###   ########.fr       */
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

void	error_msg(char *msg);
void	ft_error(void);
void	cmd_error(char **cmd);
void	check_malloc(void *str);

t_mini	ft_init_mini(void);
void	ft_destroy_mini(t_mini *minishell);

void	ft_execution(t_mini *minishell);

// - PARSING - //

char	*ft_clean_input(char *input);

int		ft_syntax_checker(char *str);
int		ft_consistency_checker(char **str);

char	*ft_analyze_input(char *input);
char	*ft_deliver_input(char **str);

#endif
