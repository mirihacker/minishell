/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:20:50 by smiranda          #+#    #+#             */
/*   Updated: 2024/07/25 12:10:53 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_mini *mini;

void initialize_env(char **envp) //tb added to main
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

char *get_env(char *key)
{
   t_list	*ptr;
   int lkey;
   char *env_var;

	lkey = ft_strlen(key);
	ptr = mini->env_list;
	if (!ft_strncmp(key, "?", 2))
		return (ft_itoa(mini->exit_code));
	while (ptr)
	{	
		env_var = ptr->content;
		if (!ft_strncmp(env_var, key, lkey) && env_var[lkey] == '=')
			return (ft_strchr(ptr->content, '=') + 1);
		ptr = ptr->next;
	}
	return (NULL);
}

char	*envvar_handler(char **start, char *str)
{
	char	*end;
	char	*env;
	char	*value;
	char	*tmp;

	end = ++(*start);
	if (ft_isdigit(*end) || ft_strchr("!#$*-?@_", *end))
		end++;
	else
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
	env = ft_substr(*start, 0, end - *start);
	*start = --end;
	value = get_env(env);
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
