/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:55:18 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 17:38:11 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "minishell.h"



/* process_ast.c */
void	traverse_ast(t_node *tree);


/* signal_handler.c */
void	handle_ignored_signal(int signum);
void	handle_sigint(int signum);
void	setup_signal_handler(void);
void	disable_ctrl_echo(void);
void	enable_ctrl_echo(void);
#endif