/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:31:02 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 20:49:28 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	free_node(t_list **ptr)
{
	if (*ptr)
	{
		if ((*ptr)->content)
		{
			free((*ptr)->content);
			(*ptr)->content = NULL;
		}
		free(*ptr);
		*ptr = NULL;
	}
}

static void	delete_env(char *argv, t_mini *mini)
{
	t_list	*env;
	t_list	*prev;
	char	*env_var;

	env = mini->env_list;
	prev = NULL;
	while (env)
	{
		env_var = (char *)env->content;
		if (!ft_strncmp(env_var, argv, ft_strlen(argv))
			&& env_var[ft_strlen(argv)] == '=')
		{
			if (prev)
				prev->next = env->next;
			else
				mini->env_list = env->next;
			free_node(&env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	builtin_unset(char **argv)
{
	int		exit_code;
	t_mini	*mini;

	exit_code = EXIT_SUCCESS;
	argv++;
	mini = get_mini();
	if (*argv && is_option(*argv, "unset"))
		return (EXIT_FAILURE);
	while (*argv)
	{
		if (!ft_search_env(*argv) || ft_strchr(*argv, '='))
		{
			print_error("unset", *argv, "not a valid identifier");
			exit_code = EXIT_FAILURE;
		}
		else
			delete_env(*argv, mini);
		argv++;
	}
	return (exit_code);
}
