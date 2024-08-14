/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:55:18 by eahn              #+#    #+#             */
/*   Updated: 2024/08/14 14:24:10 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "minishell.h"
# include "parser.h"

typedef enum s_node_type	t_node_type;
typedef struct s_cmd		t_cmd;
typedef enum s_cmd_type		t_cmd_type;

/* execute_with_fork.c */
void						execute_with_fork(t_node *node, t_cmd *last_cmd);

/* execute_without_fork.c */
void						execute_without_fork(t_node *cmd_node,
								t_cmd_type cmd_type);

/* fork_utils.c */
t_cmd						*get_last_cmd(void);
t_cmd						*get_new_cmd(void);
void						reset_cmd_list(void);
void						free_ast(t_node *node);

/* pipe_utils.c */
void						ft_dup2(int old_fd, int new_fd);
void						ft_close(int fd);
void						ft_pipe(t_cmd *cmd);

/* process_ast.c */
void						traverse_ast(t_node *tree);

/* redirect.c */
int							redirect_without_fork(t_node *rdr_node);

/* redirect_forked.c */
void						redirect_with_fork(t_node *rdr_node);

/* redirect_utils.c */
int							verify_system_call(int res, char *str);
int							ft_open(char *filename, int open_flag, int mode);

/* signal_handler.c */
void						handle_ignored_signal(int signum);
void						handle_sigint(int signum);
void						setup_signal_handler(void);
void						disable_ctrl_echo(void);
void						enable_ctrl_echo(void);

/* wait_handler */
void						handle_final_child(int final_child_status);
void						wait_for_children(void);

#endif
