/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:20:50 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 16:30:35 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


char	*get_var_val(char *key)
{
	t_list *ptr;
	int lkey;
	char *env_var;
	t_mini *mini;

	lkey = ft_strlen(key);
	mini = get_mini();
	ptr = mini->env_list;

	if (!ft_strncmp(key, "?", 2))
		return (ft_itoa(mini->exit_code));
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

// static char	*get_var_name(char **start)
// {
// 	char	*end;
// 	char	*env;

// 	// Move the end pointer to the next character after the start pointer (pass the '$)
// 	end = ++(*start);
// 	// Check if the first character is a digit or special char,
// 	//	if so move the end pointer to the next char
// 	if (ft_isdigit(*end) || ft_strchr("!#$*-?@_", *end))
// 		end++;
// 	else
// 		// If the first character is a letter, underscore, or digit,
// 		//	move the end pointer to the next character (until the end)
// 		while (*end && (ft_isalnum(*end) || *end == '_'))
// 			end++;
// 	// Create a substring from the start pointer to the end of var name
// 	env = ft_substr(*start, 0, end - *start);
// 	// Move the start pointer to the end of var name
// 	*start = --end;
// 	return (env);
// }

char	*envvar_handler(char **start, char *str) //DONE
{
	char	*value;
	char	*tmp;
	char	*env;
	char	*end;

	end = ++(*start);
	if (ft_isdigit(*end) || ft_strchr("!#$*-?@_", *end))
		end++;
	else
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
	env = ft_substr(*start, 0, end - *start);
	*start = --end;
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
