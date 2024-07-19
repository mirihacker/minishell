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

#include "../inc/minishell.h"

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

bool	check_param(char *str)
{
	str++;
	return (*str && (ft_isalnum(*str) || ft_strchr("!#$*-?@_", *str)));
}

char	*substitute_env(char **start, char *str) //---TBD----
{
}

char	*ft_realloc(char *prev, char word)
{
	char	*new_buffer;
	int		old_length;
	int		i;

	old_length = 0;
	if (prev)
	{
		while (prev[old_length])
			old_length++;
	}
	new_buffer = ft_calloc((old_length + 2), 1);
	i = 0;
	while (i < old_length)
	{
		new_buffer[i] = prev[i];
		i++;
	}
	if (prev)
		free(prev);
	new_buffer[i] = word;
	return (new_buffer);
}

char	*remove_quote(t_token *token, char *value)
{
	char	*result;
	char	quote;

	result = ft_calloc(1, 1);
	quote = 0; // Initialize quote to 0 (no quote)
	while (*value)
	{
		if (!quote && ft_strchr("'\"", *value)) // if value contains quote
			quote = *value;
		else if (quote == *value) // if quote found, quote = 0;
			quote = 0;
		else
		{
			if (token->value != '<<')
			{
				if (*value == '$' && quote != '\'' && check_param(value))
					result = substitute_env(&value, result); // ------TBD---
			}
			else
				result = ft_realloc(result, *value);
		}
		value++;
	}
	return (result);
}

static int	case_pipe(t_token *head, t_node *ptr)
{
	if (!(head)->next || head->next->type == TOKEN_PIPE)
		return (-1);
	if (!(ptr->left->left || ptr->left->right))
		return (-1);
	ptr->right = node_sequence();
	ptr = ptr->right; // tbc
}

int	sort_node(t_token **head, t_node **ptr)
{
	bool	result;
	char	*word;

	if ((*head)->type == TOKEN_PIPE)
	{
		result = case_pipe(*head, *ptr);
		ptr = ptr->right;
	}
	else if (head->type == TOKEN_SYMBOL)
	{
		ptr = ptr->left;
		if (!(head->next) || head->next->type != TOKEN_STRING)
			return (-1);
		word = remove_quote(head, head->next->value);
	}
	else // TOKEN_STRING
	{
		ptr = ptr->left;
	}
}

static void	build_ast(t_token *tokens)
{
	t_node	*root;
	t_node	*ptr;
	bool	flag;

	root = nsequence();
	ptr = root;
	while (tokens)
	{
		flag = sort_node(&tokens, &ptr);
		// error handler missing
		tokens = tokens->next;
	}
}

void	parser(t_token *tokens)
{
	t_node *root;

	if (tokens)
	{
		root = build_ast(tokens);
		if (root)
			read_ast(root); // tbd
		free_token(tokens);
		free_ast(root); // tbd
	}
}