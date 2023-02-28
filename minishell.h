/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:08 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/28 15:02:06 by vdelafos         ###   ########.fr       */
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
# include <fcntl.h>

int	g_last_return_code;

typedef struct s_cmd
{
	int		infile_mod; // here_doc (cmd << LIMITER) = 1 ou normal (< file) = 0 ou aucun (\) = -1
	int		outfile_mod; // append (>>) = 1 ou normal (> file) = 0 ou aucun (\) = -1
	int		infile_fd; // fd du fichier d'entrée (pour l'execve)
	int		outfile_fd; // fd du fichier de sortie (pour l'execve)
	char	*limiter; // si infile_mod = 1
	char	*infile; // nom du fichier d'entrée
	char	*outfile; // nom du fichier de sortie
	char	**envp; // environnement
	char	**cmd_path_lst; // le path de toutes les commandes
	char	**cmd_arg; // la commande et ses arguments
}	t_cmd;

typedef struct s_mini
{
	int		nb_cmd;
	char	**envp;
	char	***cmd_lst;
}	t_mini

// #-# MAIN #-# //

char	*ft_get_name(void);

// #-# EXECUTION #-# //

void	ft_error_msg(char *msg);
void	ft_error(void);
void	ft_cmd_error(char **cmd);
void	ft_check_malloc(void *str);

t_mini	*ft_init_mini(char *envp[]);
void	ft_destroy_mini(t_mini *minishell);

char	**ft_find_path(char *envp[]);

void	ft_execution(t_mini *minishell);
void	ft_pipex(t_mini *minishell);
void	ft_child(int (*fd)[2], int i, t_mini *minishell);
char	*ft_check_access(int i, t_mini *minishell);

// #-# PARSING #-# //

char	*ft_analyze_input(char *input);

// CLEANERS //

char	*ft_input_cleaner(char *input);
char 	*ft_add_spaces_for_pipes(char *str);
char 	*ft_hide_spaces_in_quotes(char *str);
char 	*ft_remove_quotes(char *str);
char 	*ft_separate_chevrons(char *str);
char 	*ft_stick_chevrons(char *str);
char	**ft_repair_spaces_in_quotes(char **strf);

// SYNTAX CHECKERS //

int		ft_syntax_checker(char **str);
int		ft_pipe_checker(char **str);
int		ft_chevron_checker(char **str);
int		ft_quote_checker(char *str);

// CONSISTENCY CHECKERS //

int		ft_consistency_checker(char **str);

// DISTRIBUTION //

char	***ft_share_off(char **str);

#endif
