/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:08 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/14 09:41:31 by vdelafos         ###   ########.fr       */
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
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct s_global
{
	int	g_pid;
	int	g_last_return_code;
}	t_global;

typedef struct s_cmd
{
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_path_lst;
	char	**cmd_arg;
}	t_cmd;

typedef	struct s_mini_tools
{
	char	*pwd;
	char	*old_pwd;
	char	*home_directory;
	char	**envp;
}	t_mini_tools;

typedef struct s_mini
{
	int				nb_cmd;
	char			***cmd_lst;
	t_mini_tools	*mini_tools;
}	t_mini;

typedef struct s_nb
{
	int	j;
	int	nb_to_add;
	int	len_cmd_arg;
	int	id_str_to_add;
}	t_nb;

t_global	*g_global;

// #-# MAIN #-# //

char	*ft_get_name(void);
int		ft_verify_characters(char *str);

void	ft_handle_signal(int signal);
void	ft_clean_stdin(void);

void	rl_replace_line(const char *text, int clear_undo);

// #-# BUILT-INS #-# //

char	*ft_get_pwd(char **envp);

int		ft_echo_builtins(char **cmd_lst);
int		ft_env_builtins(char **envp);
int		ft_pwd_builtins(t_mini_tools *mini_tools);
int		ft_export_builtins(char **cmd_arg, t_mini *minishell);
void	ft_exit_builtins(t_cmd *cmd_struct);

int		ft_unset_builtins(t_mini *minishell, char **cmd_arg);
int		ft_cd_builtins(char **cmd_arg, t_mini *minishell);

// #-# EXECUTION #-# //

char	*ft_check_access(t_cmd *cmd_struct);

void	ft_here_doc(t_cmd *cmd_struct, char *limiter);
void	file_not_open(t_cmd *cmd_struct, char *file_name);

void	ft_add_to_cmd_arg(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb);

void	ft_child(int (*fd)[2], int i, t_mini *minishell);
void	ft_child_one_cmd(int (*fd)[2], int i, t_mini *minishell, t_cmd *cmd_struct);

void	ft_build_struct_cmd(t_mini *minishell, t_cmd *cmd_struct, int i);
void	ft_build_little_struct_cmd(t_mini *minishell, t_cmd *cmd_struct, int i);

void	ft_error_msg(char *msg);
void	ft_error(void);
void	ft_cmd_error(char **cmd);
void	ft_check_malloc(void *str);
void	ft_msg(char	*msg);

void	ft_execution(t_mini *minishell);

t_cmd	*ft_exec_one_cmd(t_mini *minishell);

char	**ft_find_path(char *envp[]);

// INITIALIZATION //

t_cmd			*ft_init_cmd(t_mini *minishell);
void			ft_destroy_cmd(t_cmd *cmd_struct);
t_mini			*ft_init_mini(t_mini_tools *mini_tools);
void			ft_destroy_mini(t_mini *minishell);
t_mini_tools	*ft_init_mini_tools(char *envp[], char **argv);
void			ft_destroy_mini_tools(t_mini_tools *mini_tools);

char			**ft_cpy_envp(char *envp[], char **argv);

char			*ft_get_home(char **envp);

// #-# PARSING #-# //

int		ft_analyze_input(char *input, t_mini *minishell);
char	***ft_share_off(char **str);

// CLEANERS //

char	*ft_input_cleaner(char *input);
char	*ft_add_spaces_for_pipes(char *str);
char	*ft_hide_spaces_in_quotes(char *str);
char	*ft_separate_chevrons(char *str);
char	*ft_stick_chevrons(char *str);
char	**ft_repair_spaces_in_quotes(char **strf);

char	**ft_remove_quotes(char **cmd_arg);
char	*ft_substitute_str(char *str);

// SYNTAX CHECKERS //

char	**ft_check_variables(char **str, t_mini *minishell);
char	*ft_get_variable(char *variable, t_mini *minishell);
char	*ft_replace(char *input, t_mini *minishell);
int		ft_what_should_be_done(char *input);

int		ft_syntax_checker(char **str);
int		ft_pipe_checker(char **str);
int		ft_chevron_checker(char **str);
int		ft_quote_checker(char *str);

#endif
