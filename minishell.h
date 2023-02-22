/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:08 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/22 14:38:42 by vdelafos         ###   ########.fr       */
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

	char	**cmd_path_lst;
	char	***cmd_lst;
}	t_mini;

// - MAIN - //

char	*ft_get_name(void);

// - EXECUTION - //

void	ft_error_msg(char *msg);
void	ft_error(void);
void	ft_cmd_error(char **cmd);
void	ft_check_malloc(void *str);

t_mini	*ft_init_mini(void);
void	ft_destroy_mini(t_mini *minishell);

char	**ft_find_path(void);

void	ft_execution(t_mini *minishell);

// - PARSING - //

char	*ft_clean_input(char *input);

int		ft_syntax_checker(char *str);
int		ft_consistency_checker(char **str);

char	*ft_analyze_input(char *input);
char	*ft_deliver_input(char **str);

#endif
