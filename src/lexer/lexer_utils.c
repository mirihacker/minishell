/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:28:41 by eahn              #+#    #+#             */
/*   Updated: 2024/08/15 16:42:05 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Checks if the quoted string is properly closed.
 * @return 0 if the quote is closed, -1 if the syntax error occurs.
 */
int	check_quote(char **end, t_token *tokens)
{
	char	quote;
	char	*str;
	t_mini	*mini;

	mini = get_mini();
	quote = **end;
	str = *end + 1;
	while (*str && *str != quote)
		str++;
	*end = str;
	if (*str == quote)
		return (0);
	free_tokens(tokens);
	ft_putendl_fd("Syntax error: unmatched quote", STDERR_FILENO);
	mini->exit_code = SYNTAX_ERROR;
	return (-1);
}

/**
 * @brief Adds a new token to the end of the token list.
 * @param list A pointer to the head of the token list.
 * @param new The new token to be added to the list.
 */
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

/**
 * @brief Frees a linked list of tokens.
 */
void	free_tokens(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (list)
	{
		temp = list->next;
		free(list->value);
		list->value = NULL;
		free(list);
		list = temp;
	}
}
