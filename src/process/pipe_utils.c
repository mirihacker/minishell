/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:45:13 by eahn              #+#    #+#             */
/*   Updated: 2024/08/13 19:55:11 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	ft_dup2(int old_fd, int new_fd)
{
	int	ret;

	ret = dup2(old_fd, new_fd);
	if (ret < 0)
		exit_error("dup2()", strerror(errno), EXIT_FAILURE);
}

void	ft_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret < 0)
		perror("close() error");
		// exit_error("close()", strerror(errno), EXIT_FAILURE); 
}

void	ft_pipe(t_cmd *cmd)
{
	int ret;

	int pipe_fds[2]; // 0: read, 1: write
	ret = pipe(pipe_fds);
	if (ret < 0)
		exit_error("pipe()", strerror(errno), EXIT_FAILURE);
	cmd->fd_in = pipe_fds[0];  // read_end
	cmd->fd_out = pipe_fds[1]; // write_end
}