# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:54:59 by eahn              #+#    #+#              #
#    Updated: 2024/08/09 12:28:07 by eahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

INC_DIR = ./inc/
SRC_DIR = ./src/
LIB_DIR	=	./libft/
LIB		=	$(LIB_DIR)libft.a


SRCS	 	= src/main.c \
			src/lexer/lexer.c \

NEW_SRCS = $(addprefix $(SRC_DIR), $(SRCS))

OBJS = $(NEW_SRCS:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIB_DIR) -c $< -o $@

$(NAME)	: $(OBJS) $(LIB)
		@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
		
$(LIB)	:
	@make -C $(LIB_DIR)

all: $(NAME)

clean:
		@make -C $(LIB_DIR) fclean
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
