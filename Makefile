NAME = minishell

LIBFT = libft
LIBFA = libft.a
READLINE = -lreadline

CC = cc
CFLAGS = -Wall -Wextra -Werror -g  # -fsanitize=address
RM = rm -f

SRC = 	srcs/main.c \
srcs/execution.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -Ilibft -I/usr/include -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) $(READLINE) -ldl -lft -o $(NAME)

$(LIBFT)/$(LIBFA):
	@$(MAKE) -C $(LIBFT)

$(LIBFT)/%.o: $(LIBFT)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

clean:
	make -C $(LIBFT) clean
	$(RM) $(OBJ)


fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)
re: fclean all


.PHONY: all clean fclean re
