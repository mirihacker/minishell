/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:02:31 by eahn              #+#    #+#             */
/*   Updated: 2024/07/22 17:54:46 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>            // tgetent, tgetflag, tgetnum, tgetstr, tgoto,
# include <dirent.h>            // opendir, readdir, closedir
# include <errno.h>             // errno
# include <fcntl.h>             // open
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line
# include <signal.h>            // signal, sigaction, sigemptyset, sigaddset
# include <stdio.h>             // printf, perror
# include <stdlib.h>            // malloc, free, exit, getenv
# include <string.h>            // strerror
# include <sys/ioctl.h>         // ioctl
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/wait.h>          // wait, waitpid, wait3, wait4
# include <term.h>              // tgetent, tgetflag, tgetnum, tgetstr, tgoto
# include <termios.h>           // tcsetattr, tcgetattr
# include <unistd.h>            // write, access, open, read, close, fork,
								// getcwd, chdir, unlink, execve, dup, dup2,
								// pipe, isatty, ttyname, ttyslot
# include <stdbool.h>           // bool, true, false

#include "../libft/libft.h"

/* LEXER */
typedef enum e_token_type
{
	TOKEN_STRING,
	TOKEN_SYMBOL,
	TOKEN_PIPE
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/* PARSER */
typedef enum s_node_type
{
	SEQUENCES, // Pipesequence
	CMD,
	CMD_STR,
	CMD_NAME,
	CMD_SUFFIX,
	CMD_ARG,
	RDR,
	RDR_O,   // >
	RDR_I,   // <
	RDR_DO,  // >>
	RDR_DI,  // <<
	FILENAME // after RDR
}					t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char 			*value; // Used for WORD and ASSIGNMENT_WORD
	struct s_node	*left;
	struct s_node	*right;
}					t_node;


typedef struct s_mini
{
	int		exit_code;
	int		h_flag;
	t_list	*env_list;
	t_list	*cmd_list;
}	t_mini;

// const char *ascii_art = 
//     " _____\n"
//     "/     \\\n"
//     "|  (*)  |\n"
//     " \\_____/\n";


t_token	*lexer(char *input);
void	free_token(t_token *tokens);

#endif