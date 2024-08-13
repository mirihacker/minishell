/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:05:16 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/13 19:16:32 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_pipe(t_token *head, t_node *ptr)
{
	if (!(head)->next || head->next->type == TOKEN_PIPE)
		return (-1);
	if (!(ptr->left->left || ptr->left->right))
		return (-1);
	ptr->right = node_sequence();
	return (0);
}

int	init_heredoc(t_token *head, char **word)
{
	char	*filename;

	if (!ft_strcmp(head->value, "<<"))
	{
		filename = heredoc_handler(*word);
		free(*word);
		if (filename == NULL)
			return (-2);
		*word = filename;
	}
	return (0);
}

int	init_redirect(t_token *head, t_node *ptr)
{
	char	*word;

	if (!(head->next) || head->next->type != TOKEN_STRING)
		return (-1);
	word = remove_quote(head->next->value);
	if (init_heredoc(head, &word) < 0)
		return (-2);
	if (!ptr->left)
		ptr->left = node_redirect(head->value, word);
	else
	{
		ptr = ptr->left;
		while (ptr->right != NULL)
			ptr = ptr->right;
		// ensure that the node will be added to the last node
		ptr->right = node_redirect(head->value, word);
	}
	return (0);
}

int	init_word(t_token *head, t_node *ptr)
{
	char *word; // value or string

	word = remove_quote(head->value);
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