/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:54 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/05 00:37:53 by eahn             ###   ########.fr       */
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
# include "../libft/libft.h"
# include <stdbool.h> // bool, true, false

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
	SEQUENCES,  // Pipesequence
	CMD,        // CMD
	CMD_STR,    // Structure -> Name // SIMPLE_CMD
	CMD_NAME,   // NAME
	CMD_SUFFIX, // Suffix -> Arg // ARGV
	CMD_ARG,    // ARG
	RDR,        // RDR
	RDR_O,      // >
	RDR_I,      // <
	RDR_DO,     // >>
	RDR_DI,     // << // HEREDOC
	FILENAME    // after RDR // FILENAME

}					t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char *value; // Used for WORD and ASSIGNMENT_WORD
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_mini
{
	int				exit_code;
	int				h_flag;
	t_list			*env_list;
	t_list			*cmd_list;
}					t_mini;

typedef struct s_cmd
{
	pid_t			pid;
	int fd_in;  // read
	int fd_out; // write
}					t_cmd;

typedef enum s_cmd_type
{
	ECHO_,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	GENERAL,
	NONE
}					t_cmd_type;

// const char *ascii_art =
//     " _____\n"
//     "/     \\\n"
//     "|  (*)  |\n"
//     " \\_____/\n";

t_token				*lexer(char *input);
void				free_tokens(t_token *list);

t_token				*lexer(char *input);
void				free_token(t_token *tokens);

// utils.c //
void				free_ptr(void **ptr);

// envvar_handler.c //
char				*envvar_handler(char **start, char *str);
char				*get_substitution(char **start);
char				*get_env(char *key);
void				initialize_env(char **envp);

// heredoc_handler.c //
char				*heredoc_handler(char *lim);
void				process_heredoc(char *lim, char *temp_fpath, int temp_fd);
void				delete_file(char **filename);
void				input_temp_fd(char *str, int tmp_fd);
char				*process_line(char *line);
char				*init_tempfile(int *temp_fd);
static char			*get_path(char *temp_dir, int i);

#endif
