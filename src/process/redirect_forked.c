/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_forked.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:50:02 by eahn              #+#    #+#             */
/*   Updated: 2024/08/15 20:24:29 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * @brief Redirects a file to a file descriptor (STDIN or STDOUT).
 * Opens a file with given flags and filename.
 * Redirects target fd to the opened fd using dup2().
 * 0644: rw-r--r-- (owner can read/write, others can only read) - default
 */
static void	forked_redirect_to_file(char *filename, int open_flag,
		int target_fd)
{
	int	file_fd;

	file_fd = ft_open(filename, open_flag, 0644);
	ft_dup2(file_fd, target_fd);
	ft_close(file_fd);
}

/**
 * @brief Redirects input from a file to standard input.
 */
static void	forked_redirect_input(char *filename)
{
	forked_redirect_to_file(filename, O_RDONLY, STDIN_FILENO);
}

/**
 * @brief Redirects output to file, overwritting of appending.
 */
static void	forked_redirect_output(t_node_type rdr_type, char *filename)
{
	int	open_flag;

	if (rdr_type == RDR_O)
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else
		open_flag = O_WRONLY | O_CREAT | O_APPEND;
	forked_redirect_to_file(filename, open_flag, STDOUT_FILENO);
}

/**
 * @brief Redirects input/output based on the RDR type.
 * - Defines RDR type and filename.
 */
static void	forked_redirect_node(t_node *rdr_node)
{
	t_node_type	rdr_type;
	char		*filename;

	rdr_type = rdr_node->left->type;
	filename = rdr_node->right->value;
	if (rdr_type == RDR_O || rdr_type == RDR_DO) // > or >>
		forked_redirect_output(rdr_type, filename);
	else // if it's <
		forked_redirect_input(filename);
}

/**
 * @brief Traverses AST nodes and recursively handles redirections.
 * - External commands with direction
 * 	 e.g. ls -l > output.txt
 * 		  grep "pattern" file.txt < input.txt
 */
void	forked_handle_redirection(t_node *rdr_node)
{
	if (!rdr_node)
		return ;
	if (rdr_node->type == P_RDR || rdr_node->type == P_HD)
		forked_redirect_node(rdr_node);
	if (rdr_node->left)
		forked_handle_redirection(rdr_node->left);
	if (rdr_node->right)
		forked_handle_redirection(rdr_node->right);
}
