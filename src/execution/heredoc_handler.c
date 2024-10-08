/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:42:25 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 17:01:35 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	delete_tmpfile(t_node *rdr)
{
	if (!rdr || rdr->type == CMD)
		return ;
	if (rdr->type == P_HD)
		unlink(rdr->right->value);
	delete_tmpfile(rdr->left);
	delete_tmpfile(rdr->right);
}

static char	*init_tempfile(int *temp_fd)
{
	static int	i;
	char		*temp_dir;
	char		*temp_fpath;

	temp_dir = get_var_val("TMPDIR");
	if (!temp_dir)
		temp_dir = "/tmp/";
	while (*temp_fd < 0)
	{
		temp_fpath = get_path(temp_dir, i);
		*temp_fd = open(temp_fpath, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC,
				0600);
		if (*temp_fd < 0)
		{
			free_ptr((void **)&temp_fpath);
			i++;
		}
	}
	return (temp_fpath);
}

char	*heredoc_handler(char *lim)
{
	char	*temp_fpath;
	int		temp_fd;
	char	*line;
	t_mini	*mini;

	temp_fd = -1;
	mini = get_mini();
	mini->h_flag = 1;
	temp_fpath = init_tempfile(&temp_fd);
	line = readline("hdoc> ");
	while (line && mini->h_flag)
	{
		line = process_line(line);
		if (!ft_strcmp(line, lim))
			break ;
		input_temp_fd(line, temp_fd);
		free_ptr((void **)&line);
		line = readline("hdoc> ");
	}
	free_ptr((void **)&line);
	close(temp_fd);
	if (!mini->h_flag)
		delete_file(&temp_fpath);
	mini->h_flag = 0;
	return (temp_fpath);
}
