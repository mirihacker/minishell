# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:54:59 by eahn              #+#    #+#              #
#    Updated: 2024/07/19 13:51:41 by smiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRC_DIR = ./src/
LIB_DIR	=	./libft/
LIB		=	$(LIB_DIR)libft.a
# LIBINC	=	./libft/

SRCS = lexer.c

NEW_SRCS = $(addprefix $(SRC_DIR), $(SRCS))

OBJS = $(NEW_SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIB_DIR) -c $< -o $@

$(NAME)	: $(OBJS) $(LIB)
		@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
		
$(LIB)	:
	@make -C $(LIB_DIR)

clean:
		@make -C $(LIB_DIR) fclean
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
