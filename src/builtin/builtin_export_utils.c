/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:45:59 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 16:59:34 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Searches for an environment variable by name.
 * - Takes the name of the environment variable.
 * - Returns a pointer to the environment variable if found.
 */

t_list	*ft_search_env(char *name)
{
	t_list	*ptr;
	char	*env_var;
	int		lkey;
	t_mini	*mini;

	mini = get_mini();
	lkey = ft_strlen(name);
	if (!lkey)
		return (NULL);
	ptr = mini->env_list;
	while (ptr)
	{
		env_var = (char *)ptr->content;
		if (!ft_strncmp(env_var, name, lkey) && env_var && env_var[lkey] == '=')
			return (ptr);
		if (ptr->next)
			ptr = ptr->next;
		else
			return (NULL);
	}
	return (NULL);
}
/**
 * @brief Updates the value of an environment variable.
 * - Takes a pointer to the environment variable, the name and the new value.
 * - Updates the value of the environment variable.
 */

static int	set_env_export(t_list *ptr, char *name, char *value)
{
	char	*new_env_var;
	char	*temp;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (EXIT_FAILURE);
	new_env_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_env_var)
		return (EXIT_FAILURE);
	free(ptr->content);
	ptr->content = new_env_var;
	return (EXIT_SUCCESS);
}

/**
 * @brief Adds environment variables to the end
 * with name and value extracted from argv.
 */
static int	put_env(char *name, char *value)
{
	t_mini	*mini;
	char	*new_env_var;
	char	*temp;

	mini = get_mini();
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (EXIT_FAILURE);
	new_env_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_env_var)
		return (EXIT_FAILURE);
	ft_lstadd_back(&(mini->env_list), ft_lstnew(new_env_var));
	return (EXIT_SUCCESS);
}

/**
 * @brief Adds environment variables with empty value.
 * - Takes from argv the name of the environment variable.
 * - If the name is not an environment variable,
	adds it to the list with empty string as value.
 */

int	ft_empty_env(char **argv)
{
	int		add_empty_env;
	t_list	*env_entry;

	env_entry = ft_search_env(*argv);
	if (!env_entry)
	{
		add_empty_env = put_env(*argv, "");
		if (add_empty_env == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Adds or updates environment variables with name and value.
 * - Takes from argv the name and value of the environment variable.
 * - If the name is already an environment variable, updates the value.
 * - If the name is not an environment variable, adds it to the list.
 */

int	ft_add_env(char *argv)
{
	char	*name;
	char	*value;
	t_list	*env_entry;
	int		flag;

	name = ft_substr(argv, 0, ft_strchr(argv, '=') - argv);
	value = ft_strdup(ft_strchr(argv, '=') + 1);
	if (!name || !value)
		return (EXIT_FAILURE);
	env_entry = ft_search_env(name);
	if (env_entry)
		flag = set_env_export(env_entry, name, value);
	else
		flag = put_env(name, value);
	free(name);
	free(value);
	if (flag == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
