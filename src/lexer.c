/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:35 by eahn              #+#    #+#             */
/*   Updated: 2024/07/23 13:39:22 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*new_token(char *value)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (ft_strchr("<>|", *value))
	{
		if (*value == '|')
			new->type = TOKEN_PIPE;
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

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*tmp;

	tmp = *list;
	if (!*list)
	{
		*list = new;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

int	check_quote(char **end, t_token *tokens)
{
	char	quote;
	char	*str;

	quote = **end;
	str = *end + 1;
	while (*str && *str != quote)
		str++;
	*end = str;
	if (*str == quote)
		return (0);
	free_tokens(tokens);
	ft_putendl_fd("Syntax error: unmatched quote", STDERR_FILENO);
	return (-1);
}

char	*get_token_value(char **input, t_token *tokens)
{
	char	*token_value;
	char	*end;

	end = *input;
	while (*end && !ft_strchr("<>| \t\n\v\f\r", *end))
	{
		if (ft_strchr("'\"", *end))
			if (check_quote(&end, tokens))
				return (NULL);
		end++;
	}
	if (*end && ft_strchr("<>|", **input))
		if (**input == *++end && **input != '|')
			end++;
	token_value = ft_substr(*input, 0, (end - *input));
	*input = end;
	return (token_value);
}

void	skip_whitespace(char **input)
{
	while (**input && ft_strchr("\t\n\v\f\r ", **input))
		(*input)++;
}

t_token	*extract_token(char *input)
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
				return (NULL);
			add_token(&tokens, new_token(token_value));
		}
	}
	return (tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = extract_token(input);
	// parser(tokens);
	return (tokens);
}
