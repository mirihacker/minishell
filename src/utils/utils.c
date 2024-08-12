/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:12:58 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 19:58:54 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_arg(char **argv)
{
	int	args;

	args = 0;
	while (*argv)
	{
		args++;
		argv++;
	}
	return (args + 1); // +1 for the NULL pointer at the end
}

t_mini	*get_mini(void)
{
	static t_mini	mini;

	return (&mini);
}

// example:
//	(mini()->in_fd) = STDIN_FILENO;
//	(mini()->out_fd) = STDOUT_FILENO;
