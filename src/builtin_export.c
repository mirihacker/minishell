/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:31:17 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/08 22:05:09 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_export(char **argv)
{
    char *name;
    char *value;

    if (ft_strchr(argv, '='))
    {
        name = ft_substr(argv, 0, ft_strchr(argv, '=') - argv);
        value = ft_strdup(ft_strchr(argv, '=') + 1);
        if (!name || !value)
            return (EXIT_FAILURE);
        if (ft_getenv(name)) //to do : check if the name is valid
            ft_setenv(name, value); //to do : check if the value is valid
        else
            ft_putenv(argv); //to do : check if the name is valid
        free(name);
        free(value);
    }
    else
    {
        if (ft_getenv(argv)) //to do
            ft_setenv(argv, "");
        else
            ft_putenv(argv); //to do : add env to the list
    }
}

int builtin_export(char **argv)
{
    int i;

    i = 1;
    if (!argv[i])
        return(builtin_env(argv));
    if (is_option(argv[i], "export"))
        return(EXIT_FAILURE);
    while (argv[i])
    {
        ft_export(argv[i]);
        i++;
    }
    return(EXIT_SUCCESS);   
}

