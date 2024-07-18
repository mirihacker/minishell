/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:53 by eahn              #+#    #+#             */
/*   Updated: 2024/07/16 18:05:30 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*create_ast_node(t_node_type type, char *data)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (node->data)
		node->data = strdup(data); // tbd
	else
		node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node *parse_complete_command (t_token *tokens)
{
    t_node *command;
    command = parse_command(tokens);

}