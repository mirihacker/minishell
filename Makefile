# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:54:59 by eahn              #+#    #+#              #
#    Updated: 2024/08/16 17:32:09 by smiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Target name
NAME        = minishell

# Directories
INC_DIR     = ./inc/
LIB_DIR     = ./libft/
SRC_DIR     = ./src/
LEXER_DIR   = $(SRC_DIR)lexer/
PARSER_DIR  = $(SRC_DIR)parser/
PROCESS_DIR = $(SRC_DIR)process/
EXEC_DIR    = $(SRC_DIR)execution/
BUILTIN_DIR = $(SRC_DIR)builtin/
UTILS_DIR   = $(SRC_DIR)utils/
OBJ_DIR	 = ./obj/

# Library
LIB         = $(LIB_DIR)libft.a

# Source files
SRCS        = $(addprefix $(SRC_DIR), main.c) \
              $(addprefix $(LEXER_DIR), lexer.c lexer_utils.c) \
              $(addprefix $(PARSER_DIR), parser.c parser_utils.c create_node.c init_node.c) \
              $(addprefix $(PROCESS_DIR), process_ast.c execute_with_fork.c execute_without_fork.c \
              fork_utils.c pipe_utils.c redirect_forked.c redirect_utils.c redirect.c signal_handler.c wait_handler.c) \
              $(addprefix $(EXEC_DIR), execution.c execution_utils.c heredoc_handler.c heredoc_utils.c envvar_handler.c) \
              $(addprefix $(BUILTIN_DIR), builtin_cd.c builtin_cd_utils.c builtin_echo.c builtin_exit.c builtin_pwd.c \
              builtin_unset.c builtin_export.c builtin_export_utils.c builtin_env.c) \
              $(addprefix $(UTILS_DIR), error.c utils.c free.c)

# Object files
OBJS        = $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))

# Compilation rules
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIB_DIR) -c $< -o $@

# Linking rule
$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) -lreadline
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗ "     
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║ "     
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║ "     
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║ "     
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ "
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ "
	@echo "						by eahn & smiranda"

# Library build rule
$(LIB):
	@make -C $(LIB_DIR)

# General rules
all: $(NAME)

clean:
	@make -C $(LIB_DIR) fclean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean re
