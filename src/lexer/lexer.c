/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:35:11 by eahn              #+#    #+#             */
/*   Updated: 2024/07/10 13:12:03 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '"' || c == '$' || c == '\0');
}

char	*handle_quotes(const char *input, char quote_type, int *index)
{
	int		start;
	int		length;
	char	*quoted_str;

	start = *index;
	(*index)++;
	while (input[*index] != quote_type && input[*index] != '\0')
		(*index)++;
	if (input[*index] == '\0')
		return (NULL); // Error: unmatched quote
	length = *index - start;
	quoted_str = strndup(input + start + 1, length - 1);
	(*index)++;
	return (quoted_str);
}

t_token	create_token(t_token_type type, const char *value, int length)
{
	t_token	token;

	token.type = type;
	token.value = strndup(value, length);
	return (token);
}

t_token	*lexer(const char *input, int *token_count)
{
	t_token	*tokens;
	int		i;
	int		start;

	tokens = (t_token *)malloc(sizeof(t_token) * strlen(input));
	// Allocate enough space
	if (!tokens)
		return (NULL); // Error: memory allocation failed
	i = 0;
	*token_count = 0;
	while (input[i])
	{
		if (is_delimiter(input[i]))
		{
			if (input[i] == '|')
				tokens[(*token_count)++] = create_token(TOKEN_PIPE, "|", 1);
			else if (input[i] == '<' && input[i + 1] == '<')
			{
				tokens[(*token_count)++] = create_token(TOKEN_HEREDOC, "<<", 2);
				i++;
			}
			else if (input[i] == '>' && input[i + 1] == '>')
			{
				tokens[(*token_count)++] = create_token(TOKEN_REDIRECT_APPEND,
						">>", 2);
				i++;
			}
			else if (input[i] == '<')
				tokens[(*token_count)++] = create_token(TOKEN_REDIRECT_IN, "<",
						1);
			else if (input[i] == '>')
				tokens[(*token_count)++] = create_token(TOKEN_REDIRECT_OUT, ">",
						1);
			else if (input[i] == '$')
				tokens[(*token_count)++] = create_token(TOKEN_VARIABLE, "$", 1);
			else if (input[i] == '\'')
				tokens[(*token_count)++] = create_token(TOKEN_SINGLE_QUOTE, "'",
						1);
			else if (input[i] == '"')
				tokens[(*token_count)++] = create_token(TOKEN_DOUBLE_QUOTE,
						"\"", 1);
			i++;
		}
		else
		{
			start = i;
			while (!is_delimiter(input[i]))
				i++;
			tokens[(*token_count)++] = create_token(TOKEN_ARGUMENT, input
					+ start, i - start);
		}
	}
	tokens[(*token_count)++] = create_token(TOKEN_EOF, "", 0); // End of input
	return (tokens);
}

#include <stdio.h>

int	main(void)
{
	const char	*input = "echo $HOME | grep 'user' >> output.txt";
	int			token_count;
	t_token		*tokens;
	int			i;

	tokens = lexer(input, &token_count);
	if (!tokens)
	{
		printf("Lexer failed\n");
		return (1);
	}
	for (i = 0; i < token_count; i++)
	{
		printf("Token type: %d, value: %s\n", tokens[i].type, tokens[i].value);
		free(tokens[i].value); // Free each token value
	}
	free(tokens); // Free the tokens array
	return (0);
}
