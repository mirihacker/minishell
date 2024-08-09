/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:22:02 by eahn              #+#    #+#             */
/*   Updated: 2024/08/08 22:23:49 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	new_str = (char *)malloc(s1_len + s2_len + s3_len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcpy(new_str + s1_len, s2, s2_len + 1);
	ft_strlcpy(new_str + s1_len + s2_len, s3, s3_len + 1);
	return (new_str);
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

int	set_env(char *key, char *value)
{
	t_list	*ptr;
	int		lkey;

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

int	print_cd_error(char *arg, char *msg)
{
	builtin_error("cd", arg, msg);
	return (EXIT_FAILURE);
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

int	change_directory(char *path)
{
	if (chdir(path) == -1)
		return (print_cd_error((char *)path, strerror(errno)));
	return (EXIT_SUCCESS);
}

int	cd_to_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_env("OLDPWD");
	if (!oldpwd)
		return (print_cd_error(NULL, "OLDPWD not set"));
	if (change_directory(oldpwd) == EXIT_SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	cd_to_home(void)
{
	char	*home;

	home = get_env("HOME");
	if (!home)
		return (print_cd_error(NULL, "HOME not set"));
	return (change_directory(home));
}

int	builtin_cd(char **av)
{
	char	cwd[PATH_MAX];
	int		result;

	if (!getcwd(cwd, sizeof(cwd)))
		return (print_cd_error(NULL, strerror(errno)));
	if (!av[1] || ft_strncmp(av[1], "~", 2) == 0)
		result = cd_to_home();
	else if (ft_strncmp(av[1], "-", 2) == 0)
		result = cd_to_oldpwd();
	else
		result = change_directory(av[1]);
	if (result == EXIT_SUCCESS)
	{
		update_dir_env(cwd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
