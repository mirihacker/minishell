/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:07:10 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/16 16:24:15 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_param(char *str)
{
	str++;
	return (*str && (ft_isalnum(*str) || ft_strchr("!#$*-?@_", *str)));
}

char	*remove_quote(t_token_type type, char *value)
{
	char	*result;
	char	quote;

	result = ft_calloc(1, 1);
	quote = 0;
	while (*value)
	{
		if (!quote && ft_strchr("'\"", *value))
			quote = *value;
		else if (quote == *value)
			quote = 0;
		else
		{
			if (type != TOKEN_HEREDOC && *value == '$' && quote != '\''
				&& check_param(value))
				result = envvar_handler(&value, result);
			else
				result = ft_realloc(result, *value);
		}
		value++;
	}
	return (result);
}
