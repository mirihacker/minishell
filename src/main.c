/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:56 by eahn              #+#    #+#             */
/*   Updated: 2024/07/22 15:23:57 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"




int main (int ac, char **av, char **env)
{
	if (ac >= 2)
	{
		printf("Error: minishell does not accept arguments\n");
		return (1); // exit_with_error tbd
	}

	t_mini mini; // declare a t_mini instance
	init_mini(&mini, env); // initialize the t_mini with env variables


	
}