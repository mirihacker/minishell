/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:33:42 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 19:55:35 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"
# include "parser.h"

/*  execution.c */
int	execute_builtin(char **argv, t_cmd_type cmd_type);
void	execution(t_node *node);

/*  execution_utils.c */
char	**get_var_val_list(void);
void	get_cmdline(char ***cmdline, t_node *arg);


/*  envvar_handler.c */
void	initialize_env(char **envp);
char	*envvar_handler(char **start, char *str);

/*  heredoc_handler.c */
char	*heredoc_handler(char *lim);

/*  heredoc_utils.c */
void	delete_file(char **filename);
void	input_temp_fd(char *str, int tmp_fd);
char	*process_line(char *line);
char	*get_path(char *temp_dir, int i);

#endif