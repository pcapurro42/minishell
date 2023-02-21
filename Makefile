# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = minishell

SRCS = minishell.c \

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LIBFT) -lreadline $(CFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C libft

re: fclean all

clean:
	@rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
