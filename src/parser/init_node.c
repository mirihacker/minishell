/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:05:16 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/14 12:26:32 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_pipe(t_token *head, t_node *ptr)
{
	if (!(head)->next || head->next->type == TOKEN_PIPE
		|| !(ptr->left->left || ptr->left->right))
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
	}
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