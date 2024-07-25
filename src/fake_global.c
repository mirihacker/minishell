/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:58:19 by eahn              #+#    #+#             */
/*   Updated: 2024/07/25 13:29:52 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_mini	*mini(void)
{
	static t_mini	mini;

	return (&mini);
}

// example:
//	(mini()->in_fd) = STDIN_FILENO;
//	(mini()->out_fd) = STDOUT_FILENO;
