/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:20:50 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/09 13:40:48 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_mini	*mini;

void	initialize_env(char **envp) // tb added to main
{
	char *copy;

	mini = (t_mini *)ft_calloc(1, sizeof(t_mini));
	while (*envp)
	{
		copy = ft_strdup(*envp);
		ft_lstadd_back(&(mini->env_list), ft_lstnew(copy));
		envp++;
	}
}

// int	is_same_key(char *str, char *key)
// {
// 	int	key_len;

// 	key_len = ft_strlen(key);
// 	if (!ft_strncmp(str, key, key_len) && str[key_len] == '=')
// 		return (1);
// 	return (0);
// }

char	*get_var_val(char *key)
{
	t_list	*ptr;
	int		lkey;
	char	*env_var;

	
	lkey = ft_strlen(key);
	ptr = mini->env_list;
	// Check if key is a special parameter, typically holds the exit code of the last command
	// if key is equal to "?" then return the exit code
	if (!ft_strncmp(key, "?", 2))
		return (ft_itoa(mini->exit_code));
	// Iterate through the linked list of environment variables
	while (ptr)
	{
		env_var = ptr->content;
		// Check if the key is equal to the environment variable and the next char is =
		if (!ft_strncmp(env_var, key, lkey) && env_var[lkey] == '=')
			return (ft_strchr(ptr->content, '=') + 1);
		ptr = ptr->next;
	}
	return (NULL);
}

char	*get_var_name(char **start)
{
	char	*end;
	char	*env;

	// Move the end pointer to the next character after the start pointer (pass the '$)
	end = ++(*start);
	// Check if the first character is a digit or special char, if so move the end pointer to the next char
	if (ft_isdigit(*end) || ft_strchr("!#$*-?@_", *end))
		end++;
	else
		// If the first character is a letter, underscore, or digit, move the end pointer to the next character (until the end)
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
	// Create a substring from the start pointer to the end of var name
	env = ft_substr(*start, 0, end - *start);
	// Move the start pointer to the end of var name
	*start = --end;
	return (env);
}

char	*envvar_handler(char **start, char *str)
{
	char	*value;
	char	*tmp;
	char	*env;

	env = get_var_name(start);
	value = get_var_val(env);
	if (!value)
		value = "";
	if (!str)
		str = ft_calloc(1, 1);
	tmp = ft_strjoin(str, value);
	if (!ft_strncmp(env, "?", 2))
		free(value);
	free(env);
	free(str);
	return (tmp);
}
