NAME = minishell

LIBFT = libft
LIBFA = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g # -fsanitize=address
RFLAG = -lreadline

MAIN = minishell
UTILS = error init_data free_data check_line
EXEC = exec_2 execution

SRC = $(addsuffix .c, $(addprefix srcs/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
	  $(addsuffix .c, $(addprefix srcs/executor/, $(EXEC))) \

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) -L$(LIBFT) $(RFLAG) $(OBJ) -ldl -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -Ilibft -I/usr/include -O3 -c $< -o $@

$(LIBFT)/$(LIBFA):
	@$(MAKE) -C $(LIBFT)

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
