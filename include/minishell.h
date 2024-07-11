/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:33:28 by eahn              #+#    #+#             */
/*   Updated: 2024/07/10 16:01:49 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>            // tgetent, tgetflag, tgetnum, tgetstr, tgoto...
#include <dirent.h>            // opendir, readdir, closedir
#include <errno.h>             // errno
#include <fcntl.h>             // open
#include <readline/readline.h> // readline, rl_clear_history, add_history...
#include <signal.h>            // signal, sigaction, sigemptyset, kill...
#include <stdio.h>             // printf, perror
#include <stdlib.h>            // malloc, free, exit, getenv
#include <string.h>            // strerror
#include <sys/ioctl.h>         // ioctl
#include <sys/stat.h>          // stat, lstat, fstat
#include <sys/wait.h>          // wait, waitpid, wait3, wait4
#include <term.h>              // tgetent, tgetflag, tgetnum, tgetstr, tgoto...
#include <termios.h>           // tcsetattr, tcgetattr
#include <unistd.h>            // write, access, open, read, close, fork..

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,       // |
	TOKEN_IN,         // <
	TOKEN_OUT,        // >
	TOKEN_DOUBLE_IN,  // <<
	TOKEN_DOUBLE_OUT, // >>
	TOKEN_DOLLAR,     // & environment variable
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;
