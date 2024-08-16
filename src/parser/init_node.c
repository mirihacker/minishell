/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:05:16 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 16:25:30 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_pipe(t_token *head, t_node *ptr)
{
	if (!(head)->next || head->next->type == TOKEN_PIPE || !(ptr->left->left
			|| ptr->left->right))
		return (-1);
	ptr->right = node_sequence();
	return (0);
}

int	init_redirect(t_token *head, t_node *ptr)
{
	char	*word;
	char	*fname;

	if (!(head->next) || head->next->type != TOKEN_STRING)
		return (-1);
	word = remove_quote(head->type, head->next->value);
	if (head->type == TOKEN_HEREDOC)
	{
		fname = heredoc_handler(word);
		free(word);
		if (fname == NULL)
			return (-2);
		word = fname;
	}
	if (!ptr->left)
		ptr->left = node_redirect(head->value, word);
	else
	{
		ptr = ptr->left;
		while (ptr->right != NULL)
			ptr = ptr->right;
		ptr->right = node_redirect(head->value, word);
	}
	return (0);
}

int	init_word(t_token *head, t_node *ptr)
{
	char	*word;

	word = remove_quote(head->type, head->value);
	while (ptr->right != NULL)
		ptr = ptr->right;
	if (ptr->type == CMD)
	{
		ptr->value = word;
		ptr->right = node_cmd(CMD_STR, word);
	}
	else
		ptr->right = node_cmd(CMD_SUFFIX, word);
	return (0);
}
