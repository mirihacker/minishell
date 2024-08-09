/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:36:48 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 13:22:01 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef enum s_node_type
{
	SEQUENCES,  // Pipesequence
	CMD,        // CMD
	CMD_STR,    // Structure -> Name // SIMPLE_CMD
	CMD_NAME,   // NAME
	CMD_SUFFIX, // Suffix -> Arg // ARGV
	CMD_ARG,    // ARG
	RDR,        // RDR
	RDR_O,      // >
	RDR_I,      // <
	RDR_DO,     // >>
	RDR_DI,     // << // HEREDOC
	FILENAME    // after RDR // FILENAME

}					t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char *value; // Used for WORD and ASSIGNMENT_WORD
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

#endif