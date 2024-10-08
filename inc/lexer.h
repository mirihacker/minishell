/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:19:12 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 16:42:56 by smiranda         ###   ########.fr       */
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
	TOKEN_HEREDOC,
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
int					check_quote(char **end, t_token *tokens);

/* lexer.c */
t_token				*lexer(char *input);

#endif
