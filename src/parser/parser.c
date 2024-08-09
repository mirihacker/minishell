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
					result = envvar_handler(&value, result);
			}
			else
				result = ft_realloc(result, *value);
		}
		value++;
	}
	return (result);
}

static int	init_pipe(t_token *head, t_node *ptr)
{
	if (!(head)->next || head->next->type == TOKEN_PIPE)
		return (-1);
	if (!(ptr->left->left || ptr->left->right))
		return (-1);
	ptr->right = node_sequence();
	return(0);
}

static int	init_heredoc(t_token *head, char **word)
{
	char	*filename;

	if (!ft_strcmp(head->value, "<<"))
	{
		filename = handler_heredoc(*word);
		free(*word);
		if (filename == NULL)
			return (-2);
		*word = filename;
	}
	return (0);
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

static int init_redirect(t_token *head, t_node *ptr)
{
	char	*word;

	if (!(head->next) || head->next->type != TOKEN_STRING)
		return (-1);
	word = remove_quote(head, head->next->value);
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
	return(0);
}

t_node *sub_cmd(t_node_type cmd, char *value)
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

static int	init_word(t_token *head, t_node *ptr)
{
	char	*word; //value or string

	word = remove_quote(head->type, head->value);
	while (ptr->right != NULL)
		ptr = ptr->right;
	if (ptr->type == CMD)
	{
		ptr->value = word;
		ptr->right = sub_cmd(CMD_STR, word);
	}
	else
		ptr->right = sub_cmd(CMD_SUFFIX, word);
	return (0);
}

int	sort_node(t_token **head, t_node **ptr_sort)
{
	bool	result;
	char	*word;

	if ((*head)->type == TOKEN_PIPE)
	{
		result = init_pipe(*head, *ptr_sort);
		ptr_sort = (*ptr_sort)->right;
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