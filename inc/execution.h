/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:33:42 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/15 20:36:34 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"
# include "parser.h"

typedef enum s_cmd_type	t_cmd_type;
typedef struct s_node	t_node;

/*  execution.c */
t_cmd_type				cmd_type_tester(char *cmd_name);
int						execute_builtin(char **argv, t_cmd_type cmd_type);
void					execution(t_node *node);

/*  execution_utils.c */
char					*find_cmd_path(char *command);
char					**get_var_val_list(void);
void					get_cmdline(char ***cmdline, t_node *arg);

/*  envvar_handler.c */
char					*envvar_handler(char **start, char *str);
char					*get_var_val(char *key);

/*  heredoc_handler.c */
char					*heredoc_handler(char *lim);
void					delete_tmpfile(t_node *rdr);

/*  heredoc_utils.c */
void					delete_file(char **filename);
void					input_temp_fd(char *str, int tmp_fd);
char					*process_line(char *line);
char					*get_path(char *temp_dir, int i);

#endif