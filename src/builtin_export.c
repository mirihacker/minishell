/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:31:17 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 14:43:26 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int set_env(t_list *ptr, char *name, char *value)
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
int put_env(char *name, char* value)
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
        flag = set_env(env_entry, name, value); //add the new value to the env var
    else
        flag = put_env(name, value); //if the name is not an env var, add it to the list
    free(name);
    free(value);
    if (flag == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int handle_export(char *argv)
{
    int flag_em;

    if (ft_strchr(argv, '='))
        flag_em = add_env(argv);
    else
        flag_em = empty_env(&argv);
    if (flag_em == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		del(tmp->content);
		*lst = (*lst)->next;
		free(tmp);
	}
}

t_list *ft_lstsort(t_list *list)
{
    t_list *ptr;
    t_list *next;
    char *temp;

    ptr = list;
    while (ptr)
    {
        next = ptr->next;
        while (next)
        {
            if (ft_strcmp(ptr->content, next->content) > 0)
            {
                temp = ptr->content;
                ptr->content = next->content;
                next->content = temp;
            }
            next = next->next;
        }
        ptr = ptr->next;
    }
    return (list);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

t_list *copy_list(t_list *list)
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

int print_list(t_list *list)
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

int print_sort_env(void)
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
