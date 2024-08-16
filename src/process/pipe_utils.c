/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:45:13 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 11:08:16 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	ft_dup2(int old_fd, int new_fd)
{
	int	result;

	result = dup2(old_fd, new_fd);
	if (result < 0)
		exit_error("dup2()", strerror(errno), EXIT_FAILURE);
}

void	ft_close(int fd)
{
	int	result;

	result = close(fd);
	if (result < 0)
		exit_error("close()", strerror(errno), EXIT_FAILURE);
}

void	ft_pipe(t_cmd *cmd)
{
	int	result;
	int	pipe_fds[2];

	result = pipe(pipe_fds);
	if (result < 0)
		exit_error("pipe()", strerror(errno), EXIT_FAILURE);
	cmd->fd_in = pipe_fds[0];
	cmd->fd_out = pipe_fds[1];
}
