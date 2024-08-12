/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:54 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 20:13:26 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtin.h"
# include "execution.h"
# include "lexer.h"
# include "parser.h"
# include "process.h"
# include <errno.h>  // errno
# include <fcntl.h>  // open
# include <limits.h> // PATH_MAX
# include <readline/history.h>
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line
# include <signal.h>            // signal, sigaction, sigemptyset, sigaddset
# include <stdbool.h>
# include <stdbool.h>   // bool, true, false
# include <stdio.h>     // printf, perror
# include <stdlib.h>    // malloc, free, exit, getenv
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <term.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto
# include <termios.h>   // tcsetattr, tcgetattr
# include <unistd.h>

# define SYNTAX_ERROR 258

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

typedef struct s_mini
{
	int		exit_code;
	int		h_flag;
	t_list	*env_list;
	t_list	*cmd_list;
}			t_mini;

// const char *ascii_art =
//     " _____\n"
//     "/     \\\n"
//     "|  (*)  |\n"
//     " \\_____/\n";

/* utils.c */
void		exit_error(char *arg, char *msg, int exit_code);
void		print_error(const char *cmd, const char *arg, const char *msg);

/* free.c */
void		free_ptr(void **ptr);
void		free_list(t_list **head);

/* utils.c */
t_mini		*get_mini(void);

#endif
