/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:56 by eahn              #+#    #+#             */
/*   Updated: 2024/07/26 14:40:55 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Function to print tokens (for debugging)
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %s, Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

int	main(void)
{
	char	line[1024];
	t_token	*tokens;

    printf("Enter a line to tokenize: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    // Remove the newline character if present
    line[strcspn(line, "\n")] = '\0';

    tokens = lexer(line);
    if (tokens) {
        print_tokens(tokens);
        free_token(tokens);
    }

    return 0;
}

// void	init_mini(t_mini *mini, char **envp)
// {
// 	mini->env_list = NULL;
// 	mini->cmd_list = NULL;
// 	mini->exit_code = 0;
// 	while (*envp)
// 	{
// 		ft_listadd_back(&mini->env_list, ft_lstnew(*envp));
// 		envp++;
// 	}
// }

// // configures how the shell handles various signals
// void	setup_signal(void)
// {
//     // off_echoctl();                    // Turn off echo control
//     // signal(SIGINT, control_sigint);
// Handle SIGINT (Ctrl-C) with control_sigint
//     // signal(SIGQUIT, SIG_IGN);         // Ignore SIGQUIT (Ctrl-\)
// }

// void	handle_eof(char *input, t_mini *mini)
// {
// 	if (!input)
// 	{
// 		ft_putendl_fd("exit", STDERR_FILENO);
// 		exit(mini->exit_code);
// 	}
// }

// void	mini_loop(t_mini *mini)
// {
// 	char *input;

// 	input = NULL;
// 	while (42)
// 	{
// 		setup_signal(); // TBD
// 		if (input)
// 			free_ptr((void **)&input);
// 		input = readline("minishell$ ");
// 		handle_eof(input, mini);
// 		if (input && *input) // If the line is not empty
// 		{
// 			add_history(input); // Add the line to the history
// 			parse(input, mini); // Parse the line and handle the input
// 		}
// 	}
// }

// int	main(int ac, char **av, char **envp)
// {
// 	if (ac >= 2)
// 	{
// 		printf("Error: minishell does not accept arguments\n");
// 		return (EXIT_FAILURE); // exit_with_error TBD
// 	}

// 	t_mini mini;            // declare a t_mini instance
// 	init_mini(&mini, envp); // initialize the t_mini with env variables

// 	write(2, ascii_art, ft_strlen(ascii_art)); // ascii art TBD
// 	mini_loop(&mini);                          // run the main shell loop

// 	free_ptr((void **)&mini.env_list);
// 	free_ptr((void **)&mini.cmd_list);

// 	return (EXIT_SUCCESS);
// }

// hello
