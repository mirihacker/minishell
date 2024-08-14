/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:48:41 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/14 14:34:30 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_path(char *temp_dir, int i) //DONE
{
	char	*d_path;
	char	*f_path;
	char	*version;

	version = ft_itoa(i);
	d_path = ft_strjoin(temp_dir, "tmp_");
	f_path = ft_strjoin(d_path, version);
	free_ptr((void **)&d_path);
	free_ptr((void **)&version);
	return (f_path);
}

char	*process_line(char *line) //DONE
{
	char	*processed_line;
	char	*copy;

	if (!*line)
		return (line);
	copy = line;
	processed_line = NULL;
	while (*copy)
	{
		if (*copy == '$')
			processed_line = envvar_handler(&copy, processed_line);
		else
			processed_line = ft_realloc(processed_line, *copy);
		copy++;
	}
	free_ptr((void **)&line);
	return (processed_line);
}

void	input_temp_fd(char *str, int tmp_fd) //DONE`
{
	char	*tmp_str;

	tmp_str = ft_strjoin(str, "\n");
	ft_putstr_fd(tmp_str, tmp_fd);
	free(tmp_str);
	tmp_str = NULL;
}

void	delete_file(char **filename) //DONE
{
	unlink(*filename);
	free(*filename);
	*filename = NULL;
}