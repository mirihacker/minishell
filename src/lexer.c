/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:35 by eahn              #+#    #+#             */
/*   Updated: 2024/07/11 18:11:25 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '"' || c == '$' || c == '\0');
}

char	*handle_quotes(const char *input, char quote_type, int *i,
		int *is_double_quote)
{
	int		start;
	int		length;
	char	*quoted_str;

	start = *i;
	(*i)++;
	*is_double_quote = (quote_type == '"');
	while (input[*i] != quote_type && input[*i] != '\0')
	{
		if (input[*i] == '\\' && input[*i + 1] == quote_type)
			(*i)++; // Skip escaped quote
		(*i)++;
	}
	if (input[*i] == '\0')
		return (NULL); // Error: unmatched quote
						// todo: error handling with stderr
	length = *i - start;
	quoted_str = (char *)malloc(length);
	if (!quoted_str)
		return (NULL); // Error: memory allocation failed
	strncpy(quoted_str, input + start + 1, length - 1);
	quoted_str[length - 1] = '\0';
	(*i)++;
	return (quoted_str);
}

t_token	create_token(t_token_type type, const char *value, int length)
{
	t_token	token;

	token.type = type;
	token.value = (char *)malloc(length + 1);
	if (!token.value)
		token.type = TOKEN_ERROR;
	else
	{
		strncpy(token.value, value, length);
		token.value[length] = '\0';
	}
	return (token);
}

void	handle_quote_token(const char *input, t_token *tokens, int *token_count,
		int *i, char quote_type)
{
	int		is_double_quote;
	char	*quoted_str;

	quoted_str = handle_quotes(input, quote_type, i, &is_double_quote);
	if (!quoted_str)
		tokens[(*token_count)++] = create_token(TOKEN_ERROR, "Unmatched quote",
				15);
	else
	{
		if (quote_type == '\'')
			tokens[(*token_count)++] = create_token(TOKEN_SINGLE_QUOTE,
					quoted_str, strlen(quoted_str));
		else if (is_double_quote)
			tokens[(*token_count)++] = create_token(TOKEN_DOUBLE_QUOTE,
					quoted_str, strlen(quoted_str));
		free(quoted_str);
	}
}

void	handle_special_tokens(const char *input, t_token *tokens,
		int *token_count, int *i)
{
	if (input[*i] == '|')
		tokens[(*token_count)++] = create_token(TOKEN_PIPE, "|", 1);
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		tokens[(*token_count)++] = create_token(TOKEN_DIN, input + *i, 2);
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		tokens[(*token_count)++] = create_token(TOKEN_DOUT, ">>", 2);
		(*i)++;
	}
	else if (input[*i] == '<')
		tokens[(*token_count)++] = create_token(TOKEN_IN, "<", 1);
	else if (input[*i] == '>')
		tokens[(*token_count)++] = create_token(TOKEN_OUT, ">", 1);
	else if (input[*i] == '$')
		tokens[(*token_count)++] = create_token(TOKEN_VARIABLE, "$", 1);
	else if (input[*i] == '\'')
		handle_quote_token(input, tokens, token_count, i, '\'');
	else if (input[*i] == '"')
		handle_quote_token(input, tokens, token_count, i, '"');
}

void	handle_token_creation(const char *input, t_token *tokens,
		int *token_count, int *i)
{
	int		start;
	bool	is_first_token;

	is_first_token = true;
	while (input[*i])
	{
		if (is_delimiter(input[*i]))
		{
			handle_special_tokens(input, tokens, token_count, i);
			(*i)++;
		}
		else
		{
			start = *i;
			while (!is_delimiter(input[*i]))
				(*i)++;
			if (is_first_token)
			{
				tokens[(*token_count)++] = create_token(TOKEN_COMMAND, input
						+ start, *i - start);
				is_first_token = false;
			}
			else
				tokens[(*token_count)++] = create_token(TOKEN_ARGUMENT, input
						+ start, *i - start);
		}
	}
}

t_token	*lexer(const char *input, int *token_count)
{
	t_token	*tokens;
	int		i;

	i = 0;
	*token_count = 0;
	tokens = (t_token *)malloc(sizeof(t_token) * strlen(input) + 1);
	if (!tokens)
		return (NULL);
	handle_token_creation(input, tokens, token_count, &i);
	tokens[(*token_count)++] = create_token(TOKEN_EOF, "", 0);
	return (tokens);
}

int	main(void)
{
	const char *input = "cat file.txt | grep 'search term'";
	int token_count;
	t_token *tokens;
	int i;

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
	free(tokens); // Free the array of tokens
}