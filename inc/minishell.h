/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:02:31 by eahn              #+#    #+#             */
/*   Updated: 2024/07/11 12:48:24 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <dirent.h> // opendir, readdir, closedir
# include <errno.h> // errno
# include <fcntl.h> // open
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <string.h> // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termios.h> // tcsetattr, tcgetattr
# include <unistd.h> // write, access, open, read, close, fork,
	// getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
#include <stdbool.h> // bool, true, false


typedef enum e_token_type
{
    TOKEN_COMMAND, // ls
    TOKEN_ARGUMENT, // -la, "hello world", 'hello world'
    TOKEN_IN, // <
    TOKEN_OUT, // >
    TOKEN_DIN,	// <<
    TOKEN_DOUT, // >>
    TOKEN_PIPE, // |
    TOKEN_VARIABLE, // $ 
    TOKEN_SINGLE_QUOTE, // '
    TOKEN_DOUBLE_QUOTE, // "
    TOKEN_ERROR, 
    TOKEN_EOF // End of input
} t_token_type;


typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

#endif