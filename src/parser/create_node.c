/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:03:51 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 15:09:23 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*create_node(t_node_type type, char *value)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	new->type = type;
	new->value = value;
	return (new);
}

t_node	*node_sequence(void)
{
	t_node	*new;

	new = create_node(SEQUENCES, NULL);
	new->left = create_node(CMD, NULL);
	return (new);
}

t_node	*node_redirect(char *str, char *word)
{
	t_node		*new;
	t_node_type	rdr;

	if (!ft_strcmp(str, "<<"))
		rdr = RDR_DI;
	else if (*str == '<')
		rdr = RDR_I;
	else if (*str == '>')
		rdr = RDR_O;
	else
		rdr = RDR_DO;
	new = create_node(RDR, NULL);
	new->left = create_node(rdr, NULL);
	new->right = create_node(FILENAME, word);
}

t_node	*node_cmd(t_node_type cmd, char *value)
{
	t_node *new;
	t_node_type type;

	if (cmd == CMD_STR)
		type = CMD_NAME;
	else
		type = CMD_ARG;
	new = create_node(cmd, NULL);
	new->left = create_node(type, value);
	return (new);
}