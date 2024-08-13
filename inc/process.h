/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:55:18 by eahn              #+#    #+#             */
/*   Updated: 2024/08/12 20:37:40 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "minishell.h"
# include "parser.h"

struct s_node;
typedef struct s_node	t_node;

struct s_cmd;
typedef struct s_cmd	t_cmd;

/* execute_with_fork.c */
void					execute_with_fork(t_node *node, t_cmd *last_cmd);

/* execute_without_fork.c */
void					execute_without_fork(t_node *cmd_node,
							t_cmd_type cmd_type);

/* fork_utils.c */
t_cmd					*get_last_cmd(void);
t_cmd					*get_new_cmd(void);
void					free_cmd_list(void);
void					free_ast(t_node *node);

/* pipe_utils.c */
void					ft_dup2(int old_fd, int new_fd);
void					ft_close(int fd);
void					ft_pipe(t_cmd *cmd);

/* process_ast.c */
void					traverse_ast(t_node *tree);

/* redirect.c */
int						redirect_without_fork(t_node *rdr_node);

/* redirect_forked.c */
void					redirect_with_fork(t_node *rdr_node);

/* redirect_utils.c */
int						verify_system_call(int res, char *str);
int						ft_open(char *filename, int open_flag, int mode);

/* signal_handler.c */
void					handle_ignored_signal(int signum);
void					handle_sigint(int signum);
void					setup_signal_handler(void);
void					disable_ctrl_echo(void);
void					enable_ctrl_echo(void);

/* wait_handler */
void					handle_final_child(int final_child_status);
void					wait_for_children(void);

#endif