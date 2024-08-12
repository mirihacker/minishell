# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:54:59 by eahn              #+#    #+#              #
#    Updated: 2024/08/12 16:35:02 by eahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

INC_DIR = ./inc/
LIB_DIR	=	./libft/
LIB		=	$(LIB_DIR)libft.a

SRCS	 	= src/main.c \
			src/lexer/lexer.c \
			src/lexer/lexer_utils.c \
			src/parser/parser.c \
			src/parser/parser_utils.c \
			src/process/process_ast.c \
			src/process/execute_with_fork.c \
			src/process/execute_without_fork.c \
			src/process/fork_utils.c \
			src/process/redirect_forked.c \
			src/process/redirect_utils.c \
			src/process/redirect.c \
			src/process/signal_handler.c \
			src/process/wait_handler.c \
			src/execution/execution.c \
			src/execution/heredoc_handler.c \
			src/execution/envvar_handler.c \
			src/builtin/builtin_cd.c \
			src/builtin/builtin_cd_utils.c \
			src/builtin/builtin_echo.c \
			src/builtin/builtin_exit.c \
			src/builtin/builtin_pwd.c \
			src/builtin/builtin_unset.c \
			src/builtin/builtin_export.c \
			src/builtin/builtin_env.c \
			src/utils/error.c \
			src/utils/utils.c \
			src/utils/free.c

OBJS = $(SRCS:%.c=%.o)

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
