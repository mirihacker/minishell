/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:30:11 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 20:08:27 by smiranda         ###   ########.fr       */
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
	// check if the current node is a suffix type (is an option to the main cmd)
	{
		new_arg = (char **)ft_calloc(count_arg(*cmdline) + 1, sizeof(char *));
		// +1 for the following argument
		i = 0;
		while ((*cmdline)[i]) // copy existing arguments
		{
			new_arg[i] = (*cmdline)[i];
			i++;
		}
		new_arg[i] = arg->left->value; // add the new argument
		free_ptr((void **)arg);
		*cmdline = new_arg;
	}
	get_cmdline(cmdline, arg->right);
	// recursive call for the next subtree in case there is one
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

static char	*find_cmd_path(char *command)
{
	char	*path;
	char	*full_path;
	char	**paths;
	char	**tmp;

	path = get_var_val("PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return (command);
	tmp = paths;
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(path, command);
		free_ptr((void **)&path);
		if (!access(full_path, X_OK))
			break ;
		free_ptr((void **)&full_path);
		paths++;
	}
	free_paths(tmp);
	if (full_path)
		return (full_path);
	return (command);
}

static char	*get_path1(char *command)
{
	if (ft_strchr(command, '/'))
		return (command);
	return (find_cmd_path(command));
}

char	**get_var_val_list(void)
{
	int i;
	t_list *ptr;
	char **new_envp;
	t_mini *mini;

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