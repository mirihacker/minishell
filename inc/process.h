/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:55:18 by eahn              #+#    #+#             */
/*   Updated: 2024/08/12 15:25:23 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "minishell.h"
# include "parser.h"

struct s_node;
typedef struct s_node t_node;

/* process_ast.c */
void	traverse_ast(t_node *tree);

/* signal_handler.c */
void	handle_ignored_signal(int signum);
void	handle_sigint(int signum);
void	setup_signal_handler(void);
void	disable_ctrl_echo(void);
void	enable_ctrl_echo(void);
#endif