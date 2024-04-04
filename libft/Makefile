# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:58:16 by hwiemann          #+#    #+#              #
#    Updated: 2024/03/25 17:24:55 by hwiemann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

AR = ar rc

RM = rm -f

CC = cc

FLAG = -Werror -Wextra -Wall

SRC = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_printf.c \
ft_printf_helper.c \

BONUSFILES = ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c \

OBJ = $(SRC:%.c=%.o)
BONUSOBJS := $(BONUSFILES:%.c=%.o)

all: $(NAME) bonus

HEADER := libft.h

$(NAME):$(OBJ)
	$(AR) $(NAME) $(OBJ)
%.o: %.c
	$(CC) $(FLAG) -c $< -o $@
bonus: $(BONUSOBJS) $(HEADER)
	$(AR) $(NAME) $(BONUSOBJS)
clean:
	$(RM) $(OBJ)
	$(RM) $(BONUSOBJS)
fclean:clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all bonus bonusclean fclean clean re
