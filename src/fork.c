/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:00 by eahn              #+#    #+#             */
/*   Updated: 2024/07/23 16:54:25 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

// pid_t	fork(void);

int	main(void)
{
	pid_t	pid;
	int		x;

	x = 0;
	pid = fork();
	x = 1;
	if (pid > 0)
	{
		x = 2;
		printf("Parent process, %d, %d\n", getpid(), x);
	}
	else if (pid == 0)
	{
		x = 3;
		printf("Child process, %d, %d\n", getpid(), x);
	}
	return (0);
}
