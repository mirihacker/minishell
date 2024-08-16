/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:56 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 14:50:15 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	init_mini(t_mini *mini, char **envp)
// {
// 	mini->env_list = NULL;
// 	mini->cmd_list = NULL;
// 	mini->exit_code = 0;
// 	mini->h_flag = 0;
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&mini->env_list, ft_lstnew(*envp));
// 		envp++;
// 	}
// }

static void	init_mini(t_mini *mini, char **envp)
{
	char	*env_var_copy;
	t_list  *new_node;

	mini->env_list = NULL;
	mini->cmd_list = NULL;
	mini->exit_code = 0;
	mini->h_flag = 0;
	while (*envp)
	{
		env_var_copy = ft_strdup(*envp);
		if (!env_var_copy)
			exit_error("init_mini Memory Alloc failed", strerror(errno), EXIT_FAILURE);
		new_node = ft_lstnew(env_var_copy);
		if (!new_node)
			exit_error("init_mini Memory Alloc failed", strerror(errno), EXIT_FAILURE);
		ft_lstadd_back(&mini->env_list, new_node);
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
	t_mini	*mini;

	// char	*ascii_art;
	if (ac >= 2)
		exit_error(av[1], strerror(ENOENT), EXIT_FAILURE);
	mini = get_mini();
	init_mini(mini, envp);
	// ascii_art = "Your ASCII art"; // TBD
	main_loop(mini);
	return (EXIT_SUCCESS);
}
