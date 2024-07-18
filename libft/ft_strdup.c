/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:51:02 by eahn              #+#    #+#             */
/*   Updated: 2024/03/13 16:20:34 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*문자열 s1의 길이를 잰 후 동적할당을 한 후에 s1을 복사한 후, 복사된 새로운 문자열을 리턴해주는 함수*/

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (new != NULL)
	{
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
		new[i] = '\0';
	}
	return (new);
}

// int	main(void)
// {
// 	char	*original;
// 	char	*copied;
// 	char	*original_ft;
// 	char	*copied_ft;

// 	original = "Hello, World!";
// 	copied = strdup(original);
// 	printf("Original: %s\n", original);
// 	printf("Copied: %s\n", copied);
// 	free(copied);
// 	original_ft = "Hello, World!";
// 	copied_ft = ft_strdup(original_ft);
// 	printf("Original: %s\n", original_ft);
// 	printf("Copied: %s\n", copied_ft);
// 	free(copied_ft);
// 	return (0);
// }
