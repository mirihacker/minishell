/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:20:50 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 17:00:43 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_var_val(char *key)
{
	t_list	*ptr;
	int		lkey;
	char	*env_var;
	t_mini	*mini;

	lkey = ft_strlen(key);
	mini = get_mini();
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
