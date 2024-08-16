/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:22:02 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 16:58:15 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	change_directory(char *path)
{
	if (chdir(path) == -1)
		return (print_cd_error((char *)path, strerror(errno)));
	return (EXIT_SUCCESS);
}

static int	cd_to_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_var_val("OLDPWD");
	if (!oldpwd)
		return (print_cd_error(NULL, "OLDPWD not set"));
	if (change_directory(oldpwd) == EXIT_SUCCESS)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int	cd_to_home(void)
{
	char	*home;

	home = get_var_val("HOME");
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
