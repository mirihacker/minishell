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

static void ft_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	if (token->type == TOKEN_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (token->next)
		ft_putstr_fd(token->next->value, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

static int	sort_node(t_token **head, t_node **ptr_sort)
{
	int	result;

	if ((*head)->type == TOKEN_PIPE)
	{	
		write(1, "DEBUGG_PIPE\n", 12);
		result = init_pipe(*head, *ptr_sort);
		*ptr_sort = (*ptr_sort)->right;
	}
	else if ((*head)->type == TOKEN_SYMBOL || (*head)->type == TOKEN_HEREDOC)
	{	
		write(1, "DEBUGG_RDR\n", 11);
		result = init_redirect(*head, (*ptr_sort)->left);
		if (!result)
			*head = (*head)->next;
	}
	else
	{
		write(1, "DEBUGG_WORD\n", 12);
		result = init_word(*head, (*ptr_sort)->left);
	}
	return (result);
}

static t_node	*build_ast(t_token *tokens)
{
	t_node	*root;
	t_node	*ptr;
	int	flag;
	t_mini *mini;

	root = node_sequence();
	ptr = root;
	while (tokens)
	{
		flag = sort_node(&tokens, &ptr);
		if (flag < 0)
		{
			if (flag == -1)
				ft_syntax_error(tokens);
			free_ast(root);
			mini = get_mini();
			mini->exit_code = SYNTAX_ERROR;
			return (NULL);
		}
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
		free_tokens(tokens);
		free_ast(root);
	}
}