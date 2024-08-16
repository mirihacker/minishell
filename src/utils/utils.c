/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:12:58 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 16:16:58 by eahn             ###   ########.fr       */
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
	return (args + 1);
}

t_mini	*get_mini(void)
{
	static t_mini	mini;

	return (&mini);
}
