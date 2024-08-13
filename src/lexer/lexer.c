/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:35 by eahn              #+#    #+#             */
/*   Updated: 2024/08/13 18:49:44 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*create_new_token(char *value)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	if (ft_strchr(SYMBOLS, *value))
	{
		if (*value == '|')
			new->type = TOKEN_PIPE;
		else
			new->type = TOKEN_SYMBOL;
	}
	else
		new->type = TOKEN_STRING;
	new->value = value;
	return (new);
}

static char	*get_token_value(char **input, t_token *tokens)
{
	char	*end;
	char *start;
	char *token_value;

	start = *input;
	end = *input;
	while (*end && !ft_strchr(SYMBOLS WHITESPACE, *end))
	{
		if (ft_strchr("'\"", *end))
		{
			if (check_quote(&end, tokens))
				return (NULL);
		}
		end++;
	}
	if (*end && ft_strchr(SYMBOLS, *start))
	{
		if (*start == *++end && *start != '|')
			end++;
	}
	token_value = ft_substr(start, 0, (end - start));
	*input = end;
	return (token_value);
}

static t_token	*extract_token(char *input)
{
	t_token	*tokens;
	char	*token_value;

	tokens = NULL;
	while (*input)
	{
		skip_whitespace(&input);
		if (*input)
		{
			token_value = get_token_value(&input, tokens);
			if (!token_value)
			{
				free_tokens(tokens);
				return (NULL);
			}
			add_token(&tokens, create_new_token(token_value));
		}
	}
	return (tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = extract_token(input);
	if (tokens)
		parser(tokens);
	return (tokens);
}
