# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = minishell

SRCS = minishell.c \
	parsing/main_checker.c \
	parsing/syntax_checker.c \
	parsing/variable_checker.c \
	parsing/input_cleaner.c \
	parsing/cleaner_utils.c \
	parsing/share_off.c \
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
	execution/execution_one_cmd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/pwd.c \
	builtins/export.c \
	builtins/exit.c \
	builtins/unset.c \
	builtins/cd.c

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## == .C TO .O == ##

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
##	$(CC) $(LIBFT) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
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
