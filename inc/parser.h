/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:36:48 by eahn              #+#    #+#             */
/*   Updated: 2024/08/14 19:54:57 by smiranda         ###   ########.fr       */
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
	SEQUENCES,  // Pipesequence
	CMD,        // CMD
	CMD_STR,    // Structure -> Name // SIMPLE_CMD
	CMD_NAME,   // NAME
	CMD_SUFFIX, // Suffix -> Arg // ARGV
	CMD_ARG,    // ARG
	RDR,        // RDR
	P_RDR,      // IO_RDR // >, <, >>
	P_HD,       // HEREDOC, IO_HERE
	RDR_O,      // >, SYMBOL_GREATER
	RDR_I,      // <, SYMBOL_LESS
	RDR_DO,     // >>, SYMBOL_DGREAT
	RDR_DI,     // << // HEREDOC, SYMBOL_DLESS
	FILENAME    // after RDR // FILENAME

}							t_node_type;

typedef struct s_node
{
	t_node_type				type;
	char *value; // Used for WORD and ASSIGNMENT_WORD
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
