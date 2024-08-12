/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@stt.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:53 by eahn              #+#    #+#             */
/*   Updated: 2024/07/19 18:13:47 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	sort_node(t_token **head, t_node **ptr_sort)
{
	bool	result;

	if ((*head)->type == TOKEN_PIPE)
	{
		result = init_pipe(*head, *ptr_sort);
		ptr_sort = (&ptr_sort)->right;
	}
	else if ((*head)->type == TOKEN_SYMBOL)
	{
		result = init_redirect(*head, (*ptr_sort)->left);
		if (!result)
			*head = (*head)->next;
	}
	else
		result = init_word(*head, (*ptr_sort)->left);
	return (result);
}

static t_node	*build_ast(t_token *tokens)
{
	t_node	*root;
	t_node	*ptr;
	bool	flag;

	root = node_sequence();
	ptr = root;
	while (tokens)
	{
		flag = sort_node(&tokens, &ptr);
		// error handler missing
		tokens = tokens->next;
	}
	return (root);
}

void	parser(t_token *tokens)
{
	t_node *root;

	if (tokens)
	{
		root = build_ast(tokens);
		if (root)
			traverse_ast(root);
		free_token(tokens);
		free_ast(root); // tbd
	}
}