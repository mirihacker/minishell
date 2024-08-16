/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:35 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 20:35:29 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Creates a new token based on the value.
 * - If value is symbol (|, <, >), sets token type accordingly.
 * - Otherwise, sets token type as TOKEN_STRING.
 */
static t_token	*create_new_token(char *value)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	if (ft_strchr(SYMBOLS, *value))
	{
		if (*value == '|')
			new->type = TOKEN_PIPE;
		else if (value[0] == '<' && value[1] == '<')
			new->type = TOKEN_HEREDOC;
		else
			new->type = TOKEN_SYMBOL;
		new->value = value;
	}
	else
	{
		new->type = TOKEN_STRING;
		new->value = value;
	}
	return (new);
}

/**
 * @brief Finds end of current token in input.
 * @return A pointer to end of current token or NULL if umatched quote.
 */
static char	*find_token_end(char *input, t_token *tokens)
{
	char	*end;

	end = input;
	while (*end && !ft_strchr(SYMBOLS WHITESPACE, *end))
	{
		if (ft_strchr("'\"", *end))
			if (check_quote(&end, tokens))
				return (NULL);
		end++;
	}
	if (*end && ft_strchr(SYMBOLS, *input))
		if (*input == *++end && *input != '|')
			end++;
	return (end);
}

/**
 * @brief Extracts tokens from input string.
 * @return A pointer to token list.
 * - Iterates through input string and extracts tokens.
 */
static t_token	*extract_token(char *input)
{
	t_token	*tokens;
	char	*end;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(WHITESPACE, *input))
			input++;
		if (*input)
		{
			end = find_token_end(input, tokens);
			if (end && input < end)
				add_token(&tokens, create_new_token(ft_substr(input, 0, (end
								- input))));
			else if (!end)
				return (NULL);
			input = end;
		}
	}
	return (tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = extract_token(input);
	parser(tokens);
	return (tokens);
}
