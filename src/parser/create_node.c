/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:03:51 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/14 13:38:26 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*create_node(t_node_type type, char *value)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	new->type = type;
	new->value = value;
	write(1, "DEBUGG2\n", 8);
	printf("new->type: %d\n", new->type);
	printf("new->value: %s\n", new->value);
	return (new);
}

t_node	*node_sequence(void)
{
	t_node	*new;

	write(1, "DEBUGG_SEQ\n", 11);
	new = create_node(SEQUENCES, NULL);
	new->left = create_node(CMD, NULL);
	return (new);
}

t_node	*node_redirect(char *str, char *word)
{
	t_node		*new;
	t_node_type	rdr;
	t_node_type type;

	if (!ft_strcmp(str, "<<"))
	{
		rdr = P_HD;
		type = RDR_DI;
	}
	else
	{
		rdr = P_RDR;
		if (*str == '<')
			type = RDR_I;
		else if (!ft_strcmp(str, ">"))
			type = RDR_O;
		else
			type = RDR_DO;
	}
	new = create_node(RDR, NULL);
	new->left = create_node(rdr, NULL);
	new->left->left = create_node(type, NULL);
	new->left->right = create_node(FILENAME, word);
	return (new);
}

t_node	*node_cmd(t_node_type cmd, char *value)
{
	t_node *new;
	t_node_type type;

	write(1, "DEBUGG1\n", 8);
	printf("value: %s\n", value);
	if (cmd == CMD_STR)
		type = CMD_NAME;
	else
		type = CMD_ARG;
	new = create_node(cmd, NULL);
	new->left = create_node(type, value);
	return (new);
}
