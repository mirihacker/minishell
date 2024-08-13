/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:19:12 by eahn              #+#    #+#             */
/*   Updated: 2024/08/13 11:37:33 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

# define SYMBOLS "<>|"
# define WHITESPACE " \t\n\v\f\r"

typedef enum s_token_type
{
	TOKEN_STRING,
	TOKEN_SYMBOL,
	TOKEN_PIPE
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/* lexer_utils.c */
void				free_tokens(t_token *list);
void				add_token(t_token **list, t_token *new);
void				skip_whitespace(char **input);
int					check_quote(char **end, t_token *tokens);

/* lexer.c */
t_token				*lexer(char *input);

#endif