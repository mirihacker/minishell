/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:48:54 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 16:23:11 by eahn             ###   ########.fr       */
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
# include <errno.h> 
# include <fcntl.h> 
# include <limits.h> 
# include <readline/history.h>
# include <readline/readline.h> 
# include <signal.h>             
# include <stdio.h>     
# include <stdlib.h>    
# include <string.h>    
# include <sys/ioctl.h> 
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <term.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto
# include <termios.h>   // tcsetattr, tcgetattr
# include <unistd.h>

# define SYNTAX_ERROR 258

typedef struct s_cmd
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
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
	EXTERNAL,
	NONE
}			t_cmd_type;

typedef struct s_mini
{
	int		exit_code;
	int		h_flag;
	t_list	*env_list;
	t_list	*cmd_list;
}			t_mini;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;
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
void		free_env_list(t_list *env_list);

/* utils.c */
t_mini		*get_mini(void);
int			count_arg(char **argv);

#endif
