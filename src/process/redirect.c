/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:49:59 by eahn              #+#    #+#             */
/*   Updated: 2024/08/14 15:49:21 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

// 6: owner read & write (4 + 2)
// 4: group, others read-only
static int	set_redirect(char *filename, int open_flag, int target_fd)
{
	int	file_fd;
	int	res;

	file_fd = open(filename, open_flag, 0644); // 0644: rw-r--r--
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

static int	redirect_input(char *filename) // <
{
	return (set_redirect(filename, O_RDONLY, STDIN_FILENO));
}

static int	redirect_output(t_node_type rdr_type, char *filename)
{
	int	open_flag;

	if (rdr_type == RDR_O) // if it's >, overwrite with TRUNC
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else // if it's >>, append
		open_flag = O_WRONLY | O_CREAT | O_APPEND;
	return (set_redirect(filename, open_flag, STDOUT_FILENO));
}

static int	redirect_node(t_node *rdr_node)
{
	t_node_type	rdr_type;
	char		*filename;

	rdr_type = rdr_node->left->type;
	filename = rdr_node->right->value;
	if (rdr_type == RDR_I || rdr_type == RDR_DI)
		return (redirect_output(rdr_type, filename));
	return (redirect_input(filename)); // <
										// herdoc will be treated seperately
}

int	redirect_without_fork(t_node *rdr_node)
{
	if (!rdr_node)
		return (0);
	if (rdr_node->type == P_RDR || rdr_node->type == P_HD)
	{
		if (redirect_node(rdr_node) == -1)
			return (-1);
	}
	if (redirect_without_fork(rdr_node->left) == -1)
		return (-1);
	if (redirect_without_fork(rdr_node->right) == -1)
		return (-1);
	return (0);
}
