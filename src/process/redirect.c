/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:49:59 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 16:18:36 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * @brief Redirects a file to a file descriptor (STDIN or STDOUT).
 * Opens a file with given flags and filename.
 * Redirects target fd to the opened fd using dup2().
 * @param filename Name of file to redirect.
 * @param open_flag Flags to open file with.
 * @param target_fd File descriptor to redirect to.
 */
static int	redirect_to_file(char *filename, int open_flag, int target_fd)
{
	int	file_fd;
	int	res;

	file_fd = open(filename, open_flag, 0644);
	if (verify_system_call(file_fd, filename) == -1)
		return (-1);
	res = dup2(file_fd, target_fd);
	if (verify_system_call(res, "dup2()") == -1)
		return (-1);
	res = close(file_fd);
	if (verify_system_call(res, "close()") == -1)
		return (-1);
	return (0);
}

/**
 * @brief Redirects input from a file to STDIN.
 * @param filename Name of file to read input from.
 * - Uses redirect_to_file() to open file and redirect stdin to this file.
 */
static int	redirect_input_from_file(char *filename)
{
	return (redirect_to_file(filename, O_RDONLY, STDIN_FILENO));
}

/**
 * @brief Redirects output to file, overwritting of appending.
 * @return 0 on success, -1 on failure.
 * @param rdr_type Type of redirection (> or >>).
 * @param filename Name of file to redirect output to.
 * - Uses redirect_to_file() to open file and redirect output.
 */
static int	redirect_output_to_file(t_node_type rdr_type, char *filename)
{
	int	open_flag;

	if (rdr_type == RDR_O)
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else
		open_flag = O_WRONLY | O_CREAT | O_APPEND;
	return (redirect_to_file(filename, open_flag, STDOUT_FILENO));
}

/**
 * @brief Redirects input/output based on the RDR type.
 * - Defines RDR type and filename.
 */
static int	redirect_node(t_node *rdr_node)
{
	t_node_type	rdr_type;
	char		*filename;

	rdr_type = rdr_node->left->type;
	filename = rdr_node->right->value;
	if (rdr_type == RDR_O || rdr_type == RDR_DO)
		return (redirect_output_to_file(rdr_type, filename));
	return (redirect_input_from_file(filename));
}

/**
 * @brief Recursievely traverses AST to apply all rdr in command.
 * - redirection without fork - redirection with builtin commands
 *   e.g. echo "Hello, World" > file.txt
 */
int	handle_redirection(t_node *rdr_node)
{
	if (!rdr_node)
		return (0);
	if (rdr_node->type == P_RDR || rdr_node->type == P_HD)
	{
		if (redirect_node(rdr_node) == -1)
			return (-1);
	}
	if (handle_redirection(rdr_node->left) == -1)
		return (-1);
	if (handle_redirection(rdr_node->right) == -1)
		return (-1);
	return (0);
}
