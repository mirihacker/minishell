/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:42:25 by smiranda          #+#    #+#             */
/*   Updated: 2024/07/26 17:46:24 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char *get_path(char *temp_dir, int i)
{
    char *d_path;
    char *f_path;
    char *version;

    version = ft_itoa(i);
    d_path = ft_strjoin(temp_dir, "temp_");
    f_path = ft_strjoin(d_path, version);
    //functions to free d_path;
    //functions 
    return(f_path);
}

char *init_tempfile(int *temp_fd)
{
    static int i;
    char *temp_dir;
    char *temp_fpath;

    temp_dir = get_env("TMPDIR");
    if (!temp_dir)
        temp_dir = "/tmp";
    while (*temp_fd < 0)
    {
        temp_fpath = get_path(temp_dir, i);
    }
}

char *heredoc_handler(char *word)
{
    char *temp_fname;
    int temp_fd;
    char *line_read;

}