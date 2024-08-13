/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:31:17 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/13 14:25:48 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int handle_export(char *argv)
{
    int flag_em;

    if (ft_strchr(argv, '='))
        flag_em = ft_add_env(argv);
    else
        flag_em = ft_empty_env(&argv);
    if (flag_em == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

static int print_list(t_list *list)
{
    t_list *ptr;

    ptr = list;
    while (ptr)
    {
        ft_putendl_fd(ptr->content, STDOUT_FILENO);
        ptr = ptr->next;
    }
    ft_lstclear(&list, free);
    return (EXIT_SUCCESS);
}

static t_list *copy_list(t_list *list)
{
    t_list *copy;
    t_list *new;

    copy = NULL;
    while (list)
    {
        new = ft_lstnew(ft_strdup(list->content));
        if (!new)
        {
            ft_lstclear(&copy, free);
            return (NULL);
        }
        ft_lstadd_back(&copy, new);
        list = list->next;
    }
    return (copy);
}

static int print_sort_env(void)
{
    t_mini *mini;
    t_list *copy;

    mini = get_mini();
    copy = copy_list(mini->env_list);
    if (!copy)
        return (EXIT_FAILURE);
    return (print_list(ft_lstsort(copy)));
}

int builtin_export(char **argv)
{
    int i;

    i = 1;
    if (!argv[i])
        return(print_sort_env());
    if (is_option(argv[i], "export"))
        return(EXIT_FAILURE);
    while (argv[i])
    {
        if (handle_export(argv[i]) == EXIT_FAILURE)
            return(EXIT_FAILURE);
        i++;
    }
    return(EXIT_SUCCESS);  
}
