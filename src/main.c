/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:56 by eahn              #+#    #+#             */
/*   Updated: 2024/08/13 11:27:54 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_mini(t_mini *mini, char **envp)
{
	mini->env_list = NULL;
	mini->cmd_list = NULL;
	mini->exit_code = 0;
	while (*envp)
	{
		ft_lstadd_back(&mini->env_list, ft_lstnew(*envp));
		envp++;
	}
}

static void	main_loop(t_mini *mini)
{
	char	*input;

	input = NULL;
	while (42)
	{
		disable_ctrl_echo();
		signal(SIGINT, &handle_sigint);
		// Handle SIGINT(Ctrl-C)with control_sigint
		signal(SIGQUIT, SIG_IGN); // Ignore SIGQUIT (Ctrl-\)
		if (input)
			free_ptr((void **)&input);
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			exit(mini->exit_code);
		}
		if (input && *input) // If the line is not empty
		{
			add_history(input); // Add the line to the history
			lexer(input);       // Lexer the line and handle the input
		}
		free_ptr((void **)&input);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*ascii_art;

	if (ac >= 2)
		exit_error(av[1], strerror(ENOTSUP), EXIT_FAILURE);
	t_mini *mini;
	mini = get_mini();
	init_mini(mini, envp);
	ascii_art = "Your ASCII art"; //TBD
	main_loop(mini);
	// free_list(&(mini->env_list)); //TBC
	return (EXIT_SUCCESS);
}
