/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:52:31 by eahn              #+#    #+#             */
/*   Updated: 2024/08/15 20:10:45 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * @brief Checks result of a system call
 * - If result is negative, prints an error message with system's error message
 */
int	verify_system_call(int res, char *str)
{
	t_mini	*mini;

	mini = get_mini();
	if (res < 0)
	{
		print_error(str, NULL, strerror(errno));
		mini->exit_code = EXIT_FAILURE;
		return (-1);
	}
	return (0);
}

/**
 * @brief Opens a file with given flags and filename.
 * @return File descriptor if the file is opened successfully.
 */
int	ft_open(char *filename, int open_flag, int mode)
{
	int	fd;

	fd = open(filename, open_flag, mode);
	if (fd < 0)
		exit_error(filename, strerror(errno), EXIT_FAILURE);
	return (fd);
}