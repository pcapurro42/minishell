# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = minishell

SRCS = minishell.c \
	parsing/main_checker.c \
	parsing/syntax_checker.c \
	parsing/variable_checker.c \
	parsing/variable_checker_utils.c \
	parsing/input_cleaner.c \
	parsing/input_cleaner_utils.c \
	parsing/ft_share_off.c \
	parsing/ft_in_out_quotes.c \
	execution/check_access.c \
	execution/init_destroy_struct.c \
	execution/init_destroy_struct2.c \
	execution/error_msg.c \
	execution/child.c \
	execution/execution.c \
	execution/find_path.c \
	execution/file.c \
	execution/add_cmd_arg.c \
	execution/build_cmd_struct.c \
	execution/environnement.c \
	execution/create_env_lines.c \
	execution/create_env_lines2.c \
	execution/execution_one_cmd.c \
	execution/exec_case.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/pwd.c \
	builtins/export/export_one.c \
	builtins/export/export_two.c \
	builtins/export/export_three.c \
	builtins/exit.c \
	builtins/unset.c \
	builtins/cd/main_cd.c \
	builtins/cd/except_cd.c \
	builtins/cd/utils_two_cd.c \
	builtins/cd/utils_one_cd.c \

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## == .C TO .O == ##

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LIBFT) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

$(LIBFT):
	make -C libft

re: fclean all

clean:
	@rm -rf $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
