/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:36:48 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 16:44:52 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "minishell.h"

typedef struct s_token		t_token;
typedef enum s_token_type	t_token_type;

typedef enum s_node_type
{
	SEQUENCES,
	CMD,
	CMD_STR,
	CMD_NAME,
	CMD_SUFFIX,
	CMD_ARG,
	RDR,
	P_RDR,
	P_HD,
	RDR_O,
	RDR_I,
	RDR_DO,
	RDR_DI,
	FILENAME
}							t_node_type;

typedef struct s_node
{
	t_node_type				type;
	char					*value;
	struct s_node			*left;
	struct s_node			*right;
}							t_node;

/* parser.c */
void						parser(t_token *tokens);

/* create_node.c */
t_node						*node_cmd(t_node_type cmd, char *value);
t_node						*node_redirect(char *str, char *word);
t_node						*node_sequence(void);
t_node						*create_node(t_node_type type, char *value);

/* parser_utils.c */
int							check_param(char *str);
char						*remove_quote(t_token_type type, char *value);

/* init_node.c */
int							init_pipe(t_token *head, t_node *ptr);
int							init_redirect(t_token *head, t_node *ptr);
int							init_word(t_token *head, t_node *ptr);

#endif
