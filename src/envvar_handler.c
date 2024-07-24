/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:20:50 by smiranda          #+#    #+#             */
/*   Updated: 2024/07/23 17:23:26 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_mini *mini;

void initialize_env(char **envp)
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

char *get_env(char *key)
{
   t_list	*ptr;

	ptr = mini->env_list;
	if (!ft_strncmp(key, "?", 2))
		return (ft_itoa(mini->exit_code));
	while (ptr)
	{
		if (is_same_key(ptr->content, key))
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