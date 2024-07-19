/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:35 by eahn              #+#    #+#             */
/*   Updated: 2024/07/19 13:51:11 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// write(1, "DEBUGG\n", 7);

void	free_token(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
		{
			free(tokens->value);
			tokens->value = NULL;
		}
		free(tokens);
		tokens = tmp;
	}
}

// void	free_token(t_token *tokens)
// {
// 	t_token	*tmp;

// 	tmp = tokens;
// 	while (tokens)
// 	{

// 		tmp = tokens->next;
// 		free(tokens->value);
// 		tokens->value = NULL;
// 		free(tokens);
// 		tokens = tmp;
// 	}
// }

bool	check_quote(char **end, t_token *tokens)
{
	char	quote;

	if (ft_strchr("'\"'", **end))
	{
		quote = **end;
		(*end)++;
		while (**end != quote && **end)
			(*end)++;
		if (**end != quote)
		{
			free_token(tokens);
			write(1, "DEBUGG\n", 7);
			ft_putendl_fd("syntax error: unmatched quote", STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

char	*tokenization(char **input, t_token *tokens)
{
	char	*end;
	bool	result;
	char	*token;

	while (ft_strchr("\t\n\v\f\r ", **input) && **input)
		(*input)++;
	end = *input;
	while (!ft_strchr("\t\n\v\f\r |<>", *end) && *end)
	{
		result = check_quote(&end, tokens);
		if (!result)
			return (NULL); // Error: unmatched quote
		end++;
	}
	if (ft_strchr("|<>", **input) && *end)
		if (*++end == **input && **input != '|')
			end++;
	if (end > *input)
	{
		token = ft_substr(*input, 0, (end - *input));
		*input = end;
		return (token);
	}
	*input = end;
	return (NULL);
}

static t_token	*create_token(char *token_value)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (ft_strchr("<>|", *token_value))
	{
		if (*token_value == '|')
			new_token->type = TOKEN_PIPE;
		else if (*token_value == '<' || *token_value == '>')
			new_token->type = TOKEN_SYMBOL;
		new_token->value = token_value;
	}
	else
	{
		new_token->type = TOKEN_STRING;
		new_token->value = token_value;
	}
	return (new_token);
}

static void	get_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

static void	add_tokens(t_token **tokens, char *input)
{
	char	*token_value;
	t_token	*new_token;

	while (*input)
	{
		token_value = tokenization(&input, *tokens);
		if (token_value)
		{
			new_token = create_token(token_value);
			get_token(tokens, new_token);
		}
	}
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	add_tokens(&tokens, input);
	return (tokens);
}

#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	input[1024];
	t_token	*tokens;
	t_token	*tmp;
	size_t	len;

	// Prompt the user for input
	printf("Enter command: ");
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		perror("fgets");
		return (1);
	}
	// Remove trailing newline character if it exists
	len = strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	// Tokenize the input
	tokens = lexer(input);
	if (!tokens)
	{
		printf("Failed to tokenize input\n");
		return (1);
	}
	// Print the tokens
	tmp = tokens;
	while (tmp)
	{
		printf("Token: Type: %d, Value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	// Free the tokens
	free_token(tokens);
	return (0);
}
