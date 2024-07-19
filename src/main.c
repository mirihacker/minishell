/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:23:56 by eahn              #+#    #+#             */
/*   Updated: 2024/07/19 13:57:56 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	input[1024];
	t_token	*tokens;
	t_token	*tmp;
	size_t	len;

	// Prompt the user for input
	printf("Enter command: ");
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		perror("fgets");
		return (1);
	}
	// Remove trailing newline character if it exists
	len = strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	// Tokenize the input
	tokens = lexer(input);
	if (!tokens)
	{
		printf("Failed to tokenize input\n");
		return (1);
	}
	// Print the tokens
	tmp = tokens;
	while (tmp)
	{
		printf("Token: Type: %d, Value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	// Free the tokens
	free_token(tokens);
	return (0);
}
