/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:30:11 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 16:29:02 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	get_cmdline(char ***cmdline, t_node *arg)
{
	char	**new_arg;
	int		i;

	if (!arg)
		return ;
	if (arg->type == CMD_SUFFIX)
	{
		new_arg = (char **)ft_calloc(count_arg(*cmdline) + 1, sizeof(char *));
		i = 0;
		while ((*cmdline)[i])
		{
			new_arg[i] = (*cmdline)[i];
			i++;
		}
		new_arg[i] = arg->left->value;
		free_ptr((void **)cmdline);
		*cmdline = new_arg;
	}
	get_cmdline(cmdline, arg->right);
}

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free_ptr((void **)&paths[i]);
		i++;
	}
	free_ptr((void **)&paths);
}

static char	*search_in_paths(char **paths, char *command)
{
	char	*path;
	char	*full_path;

	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(path, command);
		free_ptr((void **)&path);
		if (!access(full_path, X_OK))
			return (full_path);
		free_ptr((void **)&full_path);
		paths++;
	}
	return (NULL);
}

char	*find_cmd_path(char *command)
{
	char	*path;
	char	**paths;
	char	*full_path;

	path = get_var_val("PATH");
	if (!path)
		return (command);
	paths = ft_split(path, ':');
	if (!paths)
		return (command);
	full_path = search_in_paths(paths, command);
	free_paths(paths);
	if (full_path)
		return (full_path);
	return (command);
}

char	**get_var_val_list(void)
{
	int		i;
	char	**new_envp;
	t_list	*ptr;
	t_mini	*mini;

	mini = get_mini();
	ptr = mini->env_list;
	new_envp = (char **)ft_calloc(ft_lstsize(ptr) + 1, sizeof(char *));
	i = 0;
	while (ptr)
	{
		new_envp[i] = (char *)(ptr->content);
		i++;
		ptr = ptr->next;
	}
	return (new_envp);
}
