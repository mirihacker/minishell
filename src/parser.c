/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:53 by eahn              #+#    #+#             */
/*   Updated: 2024/07/19 14:56:45 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node *create_node(t_node_type type, char *value)
{
	t_node *new;

	new = ft_calloc(1, sizeof(t_node));
	new->type = type;
	new->value = value;
	return(new);
}

t_node *node_sequence(void)
{
	t_node *new;

	new = create_node(SEQUENCES, NULL);
	new->left = create_node(CMD, NULL);
	return (new);
}

bool sort_node(t_token *head, t_node *ptr)
{
	bool result;

	if (head->type == TOKEN_PIPE)
	{
		if (!(head)->next || head->next->type == TOKEN_PIPE
		|| !(ptr->left->left || ptr->left->right))
			return(false);
		ptr->right = node_sequence();
		ptr = ptr->right; //tbc
	}
	else if (head->type == TOKEN_SYMBOL)
	{
		
	}
} 

static void build_ast(t_token *tokens)
{
	t_node *root;
	t_node *ptr;
	bool flag;

	root = node_sequence();
	ptr = root;
	while (tokens)
	{
		flag = sort_node(&tokens, &ptr);
		 // error handler missing
		tokens = tokens->next;
	}
}

void parser(t_token *tokens)
{
	t_node *root;

	if (tokens)
	{
		root = build_ast(tokens);
		if (root)
			read_ast(root); //tbd
		free_token(tokens);
		free_ast(root); // tbd
	}
}