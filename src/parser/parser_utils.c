/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:07:10 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/13 19:15:22 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_param(char *str)
{
	str++;
	return (*str && (ft_isalnum(*str) || ft_strchr("!#$*-?@_", *str)));
}

char	*remove_quote(char *value)
{
	char *result;
	char quote;

	result = ft_calloc(1, 1);
	quote = 0; // Initialize quote to 0 (no quote)
	while (*value)
	{
		if (!quote && ft_strchr("'\"", *value)) // if value contains quote
			quote = *value;
		else if (quote == *value) // if quote found, quote = 0;
			quote = 0;
		else
		{
			if (ft_strcmp(value, "<<"))
			{
				if (*value == '$' && quote != '\'' && check_param(value))
					result = envvar_handler(&value, result);
			}
			else
				result = ft_realloc(result, *value);
		}
		value++;
	}
	return (result);
}