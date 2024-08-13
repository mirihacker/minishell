/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:02:58 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/13 12:29:35 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *prev, char word)
{
	char	*new_buffer;
	int		old_length;
	int		i;

	old_length = 0;
	if (prev)
	{
		while (prev[old_length])
			old_length++;
	}
	new_buffer = ft_calloc((old_length + 2), 1);
	i = 0;
	while (i < old_length)
	{
		new_buffer[i] = prev[i];
		i++;
	}
	if (prev)
		free(prev);
	new_buffer[i] = word;
	return (new_buffer);
}