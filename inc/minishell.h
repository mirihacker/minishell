/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:54 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/09 16:42:51 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <unistd.h>           
# include "../libft/libft.h"
# include "builtin.h"
# include "execution.h"
# include "lexer.h"
# include "parser.h"
# include "process.h"
# include <limits.h>  // PATH_MAX
# include <stdbool.h> // bool, true, false

typedef struct s_mini
{
	int		exit_code;
	int		h_flag;
	t_list	*env_list;
	t_list	*cmd_list;
}			t_mini;

typedef struct s_cmd
{
	pid_t	pid;
	int fd_in;  // read
	int fd_out; // write
}			t_cmd;

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
}			t_cmd_type;

// const char *ascii_art =
//     " _____\n"
//     "/     \\\n"
//     "|  (*)  |\n"
//     " \\_____/\n";

// utils.c //
void		free_ptr(void **ptr);

// envvar_handler.c //
char		*envvar_handler(char **start, char *str);
char		*get_substitution(char **start);
char		*get_env(char *key);
void		initialize_env(char **envp);

// heredoc_handler.c //
char		*heredoc_handler(char *lim);
void		process_heredoc(char *lim, char *temp_fpath, int temp_fd);
void		delete_file(char **filename);
void		input_temp_fd(char *str, int tmp_fd);
char		*process_line(char *line);
char		*init_tempfile(int *temp_fd);
static char	*get_path(char *temp_dir, int i);

#endif
