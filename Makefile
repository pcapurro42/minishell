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
	execution/error_msg.c \
	execution/child.c \
	execution/execution.c \
	execution/find_path.c \

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## == .C TO .O == ##

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LIBFT) -lreadline $(CFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C libft

re: fclean all

clean:
	@rm -rf $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
