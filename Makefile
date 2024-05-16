NAME = minishell

LIBFT = libft
LIBFA = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RFLAG = -lreadline

MAIN = minishell
EXEC = exec_env exec_env2 execution built_in built_in_env built_in_child built_in_export exec_shell
UTILS = error error2 init_env free_data check_line delete_lists delete_lists2 utils
LEXER = lexer create_token_list lexer_utils expand_env expand_env_utils heredoc
PARSER = parser create_toex_list create_redir_list redir
SIGNALS = signals

SRC =	$(addsuffix .c, $(addprefix srcs/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
		$(addsuffix .c, $(addprefix srcs/lexer/, $(LEXER))) \
		$(addsuffix .c, $(addprefix srcs/parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix srcs/signals/, $(SIGNALS))) \
		$(addsuffix .c, $(addprefix srcs/executor/, $(EXEC))) \

TEST_SRC = srcs/testfiles.c

OBJ = $(SRC:c=o)
TEST_OBJ = $(TEST_SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) -L$(LIBFT) $(RFLAG) $(OBJ) -ldl -lft -o $(NAME)

test: $(OBJ) $(LIBFT)/$(LIBFA) $(TEST_OBJ)
	$(CC) $(CFLAGS) -L$(LIBFT) $(RFLAG) $(OBJ) $(TEST_OBJ) -ldl -lft -o $(NAME)

debug: $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) -L$(LIBFT) $(RFLAG) $(OBJ) -ldl -lft -g3 -fsanitize=address -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -Ilibft -I/usr/include -O3 -c $< -o $@

$(LIBFT)/$(LIBFA):
	@$(MAKE) -C $(LIBFT)

$(LIBFT)/%.o: $(LIBFT)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ)
	rm -f $(TEST_OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
