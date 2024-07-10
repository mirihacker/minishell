# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 17:16:57 by eahn              #+#    #+#              #
#    Updated: 2024/07/10 12:43:56 by eahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC_DIR = ./src/

SRCS = /lexer/lexer.c

NEW_SRCS = $(addprefix $(SRC_DIR), $(SRCS))

OBJS = $(NEW_SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
