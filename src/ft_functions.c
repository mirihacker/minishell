/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:19:07 by eahn              #+#    #+#             */
/*   Updated: 2024/07/25 22:23:30 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pipe(t_cmd *cmd)
{
	int	pipe_fds[2];
	int	ret;

	ret = pipe(pipe_fds);
	if (ret < 0)
		exit_with_err("pipe()", strerror(errno), EXIT_FAILURE); // TBD
	cmd->fd_in = pipe_fds[0];                                   // read_end
	cmd->fd_out = pipe_fds[1];                                  // write_end
}
