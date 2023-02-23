/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:08 by pcapurro          #+#    #+#             */
/*   Updated: 2023/02/23 08:42:05 by vdelafos         ###   ########.fr       */
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

typedef struct s_mini
{
	int		nb_cmd; // le nombre de commandes à exécuter 

	int		infile_mod; // here_doc (cmd << LIMITER) = 1 ou normal (< file) = 0 ou aucun (\) = -1
	int		outfile_mod; // append (>>) = 1 ou normal (> file) = 0 ou aucun (\) = -1

	int		infile_fd; // fd du fichier d'entrée (pour l'execve)
	int		outfile_fd; // fd du fichier de sortie (pour l'execve)

	char	*limiter; // si infile_mod = 1
	char	*infile; // nom du fichier d'entrée
	char	*outfile; // nom du fichier de sortie

	char	**envp; // environnement
	char	**cmd_path_lst; // le path de toutes les commandes
	char	***cmd_lst; // la liste des commandes à exécuter
}	t_mini;

// - MAIN - //

char	*ft_get_name(void);

// - EXECUTION - //

void	ft_error_msg(char *msg);
void	ft_error(void);
void	ft_cmd_error(char **cmd);
void	ft_check_malloc(void *str);

t_mini	*ft_init_mini(char *envp[]);
void	ft_destroy_mini(t_mini *minishell);

char	**ft_find_path(char *envp[]);

void	ft_execution(t_mini *minishell);

// - PARSING - //

char	*ft_clean_input(char *input);

int		ft_syntax_checker(char *str);
int		ft_consistency_checker(char **str);

char	*ft_analyze_input(char *input);
char	*ft_deliver_input(char **str);

#endif
