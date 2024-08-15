/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:33:17 by eahn              #+#    #+#             */
/*   Updated: 2024/08/15 20:36:31 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

/*  buitlin_cd_utils.c */
int		print_cd_error(char *arg, char *msg);
int		add_env_var(t_list **env_list, char *key, char *value);
void	update_dir_env(char *old_pwd);
int		set_env(char *key, char *value);

/*  builtin_cd.c */
int		builtin_cd(char **av);

/*  builtin_echo.c */
int		builtin_echo(char **av);

/*  builtin_env.c */
int		is_option(char *str, char *cmd);
int		builtin_env(char **argv);

/*  builtin_exit.c */
int		builtin_exit(char **av, int *exit_requested);

/*  builtin_export_utils.c */
int		ft_add_env(char *argv);
int		ft_empty_env(char **argv);
t_list	*ft_search_env(char *name);

/*  builtin_export.c */
int		builtin_export(char **argv);

/*  builtin_pwd.c */
int		builtin_pwd(char **av);

/*  builtin_unset.c */
int		builtin_unset(char **argv);

#endif