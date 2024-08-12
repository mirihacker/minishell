/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:35:39 by eahn              #+#    #+#             */
/*   Updated: 2024/08/12 15:34:33 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	print_cd_error(char *arg, char *msg)
{
	print_error("cd", arg, msg);
	return (EXIT_FAILURE);
}


int	add_env_var(t_list **env_list, char *key, char *value)
{
	char	*new_env_var;
	t_list	*new_node;

	new_env_var = ft_strjoin3(key, "=", value);
	if (!new_env_var)
		return (-1);
	new_node = ft_lstnew(new_env_var);
	if (!new_node)
	{
		free(new_env_var);
		return (-1);
	}
	ft_listadd_back(env_list, new_node);
	return (0);
}

void	update_dir_env(char *old_pwd)
{
	char	cwd[PATH_MAX];

	set_env("OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env("PWD", cwd);
	else
		print_cd_error(NULL, strerror(errno));
}

int	set_env(char *key, char *value)
{
	t_list *ptr;
	t_mini *mini;
	int lkey;

	mini = get_mini();
	lkey = ft_strlen(key);
	ptr = mini->env_list;
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, key, lkey)
			&& ((char *)ptr->content)[lkey] == '=')
		{
			free(ptr->content);
			ptr->content = ft_strjoin3(key, "=", value);
			if (!ptr->content)
				return (-1);
			return (0);
		}
		ptr = ptr->next;
	}
	return (add_env_var(&mini->env_list, key, value));
}