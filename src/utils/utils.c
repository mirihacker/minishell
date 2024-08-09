/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:12:58 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/09 14:31:11 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



t_mini	*get_mini(void)
{
	static t_mini	mini;

	return (&mini);
}

// example:
//	(mini()->in_fd) = STDIN_FILENO;
//	(mini()->out_fd) = STDOUT_FILENO;
