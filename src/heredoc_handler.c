/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:42:25 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/08 23:13:50 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_tmpfile(t_ast *rdr) // TBD
{
	// if (!rdr || rdr->type == SIMPLE_CMD)
	// 	return ;
	// if (rdr->type == IO_HERE)
	// 	unlink(rdr->right->data);
	// delete_tmpfile(rdr->left);
	// delete_tmpfile(rdr->right);
}

static char	*get_path(char *temp_dir, int i)
{
	char	*d_path;
	char	*f_path;
	char	*version;

	version = ft_itoa(i);
	d_path = ft_strjoin(temp_dir, "temp_");
	f_path = ft_strjoin(d_path, version);
	free_ptr((void **)&d_path);
	free_ptr((void **)&version);
	return (f_path);
}

char	*init_tempfile(int *temp_fd)
{
	static int	i;
	char		*temp_dir;
	char		*temp_fpath;

	temp_dir = get_env("TMPDIR");
	if (!temp_dir)
		temp_dir = "/temp/";
	while (*temp_fd < 0)
	{
		temp_fpath = get_path(temp_dir, i);
		*temp_fd = open(temp_fpath, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC,
				0600);
		if (*temp_fd)
		{
			free_ptr((void **)&temp_fpath);
			i++;
		}
	}
	return (temp_fpath);
}

char	*process_line(char *line)
{
	char	*processed_line;
	char	*copy;

	if (!*line)
		return (line);
	copy = line;
	processed_line = NULL;
	while (*copy)
	{
		if (copy == '$')
			processed_line = envvar_handler(&copy, processed_line);
		else
			processed_line = ft_realloc(&processed_line, *copy);
		copy++;
	}
	free_ptr((void **)line);
	return (processed_line);
}

void	input_temp_fd(char *str, int tmp_fd)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(str, "\n");
	ft_putstr_fd(tmp_str, tmp_fd);
	free(tmp_str);
	tmp_str = NULL;
}

void	delete_file(char **filename)
{
	unlink(*filename);
	free(*filename);
	*filename = NULL;
}

void	process_heredoc(char *lim, char *temp_fpath, int temp_fd)
{
	char	*line;

	line = readline("hdoc> ");
	while (line && mini->h_flag)
	{
		line = process_line(line);
		if (!ft_strncmp(line, lim, ft_strlen(lim) + 1))
			break ;
		input_temp_fd(line, temp_fd);
		free_ptr((void **)&line);
		line = readline("hdoc> ");
	}
	free_ptr((void **)&line);
	close(tmp_fd);
	if (!mini->h_flag)
		delete_file(&temp_fpath);
	mini->h_flag = 0;
}

char	*heredoc_handler(char *lim)
{
	char	*temp_fpath;
	int		temp_fd;
	char	*line;

	temp_fd = -1;
	mini->h_flag = 1;
	temp_fpath = init_tempfile(&temp_fd);
	process_heredoc(lim, temp_fpath, temp_fd);
	return (temp_fpath);
}
