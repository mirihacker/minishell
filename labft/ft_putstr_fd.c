/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:04:29 by eahn              #+#    #+#             */
/*   Updated: 2024/03/12 15:16:59 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putstr_fd(char *s, int fd)
// {
// 	while (*s)
// 		write(fd, s++, 1);
// }

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

// int	main(void)
// {
// 	char	str[] = "Hello World!";
// 	int		fd;

// 	fd = 1;
// 	ft_putstr_fd(str, fd);
// 	return (0);
// }
