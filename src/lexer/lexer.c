/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:35 by eahn              #+#    #+#             */
/*   Updated: 2024/08/14 02:01:59 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
		printf("new->value: %s\n", new->value);
	}
	else
	{
		new->type = TOKEN_STRING;
		new->value = value;
		printf("new->value (TOKEN_STRING): %s\n", new->value);
	}
	return (new);
}

static t_token	*extract_token(char *input)
{
	t_token	*tokens;
	char	*end;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(WHITESPACE, *input))
			input++;
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
		if (input < end)
			add_token(&tokens, create_new_token(ft_substr(input, 0, (end
							- input))));
		input = end;
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
