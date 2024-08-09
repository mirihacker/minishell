/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:28:41 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 17:23:32 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

void	skip_whitespace(char **input)
{
	while (**input && ft_strchr(WHITESPACE, **input))
		(*input)++;
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
		tmp = tmp->next;
	tmp->next = new;
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
