/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:45:59 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/13 11:58:50 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_list *search_env(char *name)
{
    t_list *ptr;
    char *env_var;
    int lkey;
    t_mini *mini;

    mini = get_mini();
    lkey = ft_strlen(name);
    if (!lkey)
        return NULL;
    ptr = mini->env_list;
    while (ptr)
    {
        env_var = (char *)ptr->content;
        if (!ft_strncmp(env_var, name, lkey) && env_var && env_var[lkey] == '=')
            return (ptr);
        ptr = ptr->next;
    }
    return (NULL);
}

static int set_env_export(t_list *ptr, char *name, char *value)
{
    char *new_env_var;
    char *temp;

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
static int put_env(char *name, char* value)
{
    t_mini *mini;
    char *new_env_var;
    char *temp;

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

int empty_env(char **argv)
{
    t_list *env_entry; //change improv
    int add_empty_env;

    env_entry = search_env(*argv);
    if (!env_entry)
    {
        add_empty_env = put_env(*argv, "");
        if (add_empty_env == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int add_env(char *argv)
{
    char *name;
    char *value;
    t_list *env_entry;
    int flag;

    name = ft_substr(argv, 0, ft_strchr(argv, '=') - argv);
    value = ft_strdup(ft_strchr(argv, '=') + 1);
    if (!name || !value)
            return (EXIT_FAILURE);
    env_entry = search_env(name);
    if (env_entry) //check if the name is already an env var
        flag = set_env_export(env_entry, name, value); //add the new value to the env var
    else
        flag = put_env(name, value); //if the name is not an env var, add it to the list
    free(name);
    free(value);
    if (flag == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}