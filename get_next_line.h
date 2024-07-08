/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:30:20 by smiranda          #+#    #+#             */
/*   Updated: 2024/05/08 13:27:52 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

/* get_next_line.c */
char	*get_next_line(int fd);
char	*ft_get_buffer(int fd, char *line_buffer);
char	*ft_get_line(char *line_buffer);
char	*ft_get_rest(char *line_buffer);

/* get_next_line_utils.c */
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif