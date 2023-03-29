/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelafos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:58:08 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/29 11:21:19 by vdelafos         ###   ########.fr       */
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

// #-# STRUCTURES #-# //

// GLOBAL STRUCTURE //

typedef struct s_global
{
	int	g_pid;
	int	g_last_return_code;
}	t_global;

// OTHERS STRUCTURES //

typedef struct s_cmd
{
	int		infile_fd;
	int		outfile_fd;
	char	**cmd_path_lst;
	char	**cmd_arg;
}	t_cmd;

typedef struct s_mini_tools
{
	char	*pwd;
	char	*old_pwd;
	char	*home_directory;
	char	**envp;
	int		path_unset;
	int		quoifeur;
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

typedef struct s_export
{
	int		return_code;
	int		nb_export;
	int		envp_len;
	int		i;
}	t_export;

t_global	*g_global;

// #-# MAIN #-# //

char			*ft_get_name(void);
void			ft_handle_signal(int signal);
void			ft_init_minishell(void);
void			ft_print_shell(int number);

void			rl_replace_line(const char *text, int clear_undo);

// #-# BUILT-INS #-# //

char			*ft_get_pwd(char **envp);

int				ft_echo_builtins(char **cmd_lst);
int				ft_env_builtins(char **envp);
int				ft_pwd_builtins(t_mini_tools *mini_tools);
void			ft_exit_builtins(t_cmd *cmd_struct);

// EXPORT //

int				ft_export_builtins(char **cmd_arg, t_mini *minishell);
int				ft_verify_errors_export(char *str);
int				ft_verify_characters_export(char *str);
int				ft_name_in_envp(char *str, char **envp);
int				ft_name_in_cmd_arg(char *str, char **cmd_arg, int j);
void			ft_replace_in_envp(char *str, char **envp);

// UNSET //

int				ft_unset_builtins(t_mini *minishell, char **cmd_arg);
void			ft_browse_unit(t_mini *minishell, char **cmd_arg, int i);
char			**ft_clean_env(char **envp);
int				ft_verify_unset_characters(char *str);
int				ft_verify_unset_errors(char *str);

// CD //

int				ft_cd_builtins(char **cmd_arg, t_mini *minishell);
int				ft_absolute_path(t_mini *minishell, char **cmd_arg, char *arg);
int				ft_relative_path(t_mini *minishell, char **cmd_arg, char *arg);
int				ft_verify_args(char *str);
char			**ft_fix_args(char **cmd_arg);
char			*ft_first_clean(char **cmd_arg);
char			*ft_last_clean(char *str);
int				ft_update_oldpwd(t_mini *minishell, char *path);
int				ft_update_pwd(t_mini *minishell, char *path);
char			*ft_step_back(char *path);
int				ft_verify_failure(char *path, char *arg, int i);
char			*ft_get_variable_again(t_mini *minishell, int a);
int				ft_handle_hyphen(t_mini *minishell);
int				ft_handle_point_point(t_mini *minishell, char *arg);
int				ft_handle_operator(t_mini *minishell, char *str, char *arg);

// #-# EXECUTION #-# //

char			*ft_check_access(t_cmd *cmd_struct);

void			ft_here_doc(t_cmd *cmd_struct, char *limiter);

void			ft_add_to_cmd_arg(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb);
int				ft_check_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb);

void			ft_child(int (*fd)[2], int i, t_mini *minishell);
void			ft_child_one_cmd(int (*fd)[2], int i, t_mini *minishell, \
	t_cmd *cmd_struct);

void			ft_build_struct_cmd(t_mini *minishell, t_cmd *cmd_struct, \
	int i);
void			ft_case_left_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb);
void			ft_case_right_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb);
void			ft_case_dbleft_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb);
void			ft_case_dright_chevron(t_mini *minishell, t_cmd *cmd_struct, \
	int i, t_nb *nb);

void			ft_error_msg(char *msg);
void			ft_cmd_error(char *msg);
void			ft_msg(char	*msg);
void			ft_error_dir(char *msg);

void			ft_execution(t_mini *minishell);

t_cmd			*ft_exec_one_cmd(t_mini *minishell);

void			ft_exec_case(char **cmd_arg, char **envp);

char			**ft_find_path(char *envp[], int path_unset);

// INITIALIZATION //

t_cmd			*ft_init_cmd(t_mini *minishell);
void			ft_destroy_cmd(t_cmd *cmd_struct);
t_mini			*ft_init_mini(t_mini_tools *mini_tools);
void			ft_destroy_mini(t_mini *minishell, char *input);
t_mini_tools	*ft_init_mini_tools(char *envp[], char **argv);
void			ft_destroy_mini_tools(t_mini_tools *mini_tools);

char			**ft_cpy_envp(char *envp[], char **argv);
int				ft_find_line_env(char **envp, char *name);

int				ft_find_nb_missing_lines(char **envp);
char			*ft_getoldpwd(void);

char			*ft_gethome(char **envp);
char			*ft_getpwd(void);
char			*ft_getshlvl(void);
char			*ft_get_(char	*pwd, char	*exec_name);
void			ft_increase_shlvl(char	**envp);

// #-# PARSING #-# //

int				ft_is_it_quoi(char *input);
void			ft_handle_quoi_feur(t_mini *minishell);

int				ft_analyze_input(char *input, t_mini *minishell);
char			***ft_share_off(char **str);

// CLEANERS //

char			*ft_input_cleaner(char *input);
char			*ft_add_spaces_for_pipes(char *str);
char			*ft_hide_things(char *str);
char			*ft_fix_chevrons_one(char *str);
char			*ft_fix_chevrons_two(char *str);
char			**ft_repair_spaces_in_quotes(char **strf);

void			ft_prepare_for_heredoc(char **str);

char			**ft_remove_quotes(char **cmd_arg);
char			*ft_substitute_str(char *str);

// SYNTAX CHECKERS //

int				ft_in_out_quotes(char *str, int i);
char			*ft_lower_input(char *str);

char			*ft_check_variables(char *str, t_mini *minishell);
char			*ft_replace_tilde(char *str, t_mini *minishell);
int				ft_to_do_quote(char *input);

int				ft_pipe_checker(char **str);
int				ft_chevron_checker_a(char *str);
int				ft_chevron_checker_b(char **str);
int				ft_quote_checker(char *str);

#endif
