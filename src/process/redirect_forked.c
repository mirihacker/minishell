/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_forked.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:50:02 by eahn              #+#    #+#             */
/*   Updated: 2024/08/14 15:39:47 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	forked_set_redirect(char *filename, int open_flag, int target_fd)
{
	int	file_fd;

	file_fd = ft_open(filename, open_flag, 0644);
	ft_dup2(file_fd, target_fd);
	ft_close(file_fd);
}

static void	forked_redirect_input(char *filename)
{
	forked_set_redirect(filename, O_RDONLY, STDIN_FILENO);
}

static void	forked_redirect_output(t_node_type rdr_type, char *filename)
{
	int	open_flag;

	if (rdr_type == RDR_O)
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else
		open_flag = O_WRONLY | O_CREAT | O_APPEND;
	forked_set_redirect(filename, open_flag, STDOUT_FILENO);
}

static void	forked_redirect_node(t_node *rdr_node)
{
	t_node_type	rdr_type;
	char		*filename;

	rdr_type = rdr_node->left->type;
	filename = rdr_node->right->value;
	if (rdr_type == RDR_I || rdr_type == RDR_DI) // if it's > or >>
		forked_redirect_output(rdr_type, filename);
	else // if it's <
		forked_redirect_input(filename);
}

void	redirect_with_fork(t_node *rdr_node)
{
	if (!rdr_node)
		return ;
	if (rdr_node->type == P_RDR || rdr_node->type == P_HD)
		forked_redirect_node(rdr_node);
	if (rdr_node->left)
		redirect_with_fork(rdr_node->left);
	if (rdr_node->right)
		redirect_with_fork(rdr_node->right);
}
