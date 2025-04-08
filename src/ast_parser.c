/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:19:27 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/08 05:13:05 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_token	*parse_command(t_token *tkn, t_node **nodeptr)
{
	t_node	*node;
	t_node	*cmdnode;

	node = create_node(NT_Cmd);
	cmdnode = node;
	while ((tkn->type & GROUP_MASK) <= GROUP1)
	{
		if ((tkn->type & GROUP_MASK) == GROUP1)
		{
			node = create_parent(tkn->type, node, NULL);
			tkn = expect_token(tkn, TK_String);
			if (!tkn)
				return (NULL);
			tkn = tkn->next;
		}
		else if (tkn->type == TK_String)
		{
			append_tkn_copy(cmdnode->data.token, tkn);
			tkn = tkn->next;
		}
	}
	*nodeptr = node;
	return (tkn);
}

t_token	*parse_pipeline(t_token *tkn, t_node **nodeptr)
{
	t_node	*node;

	parse_command(tkn, &node);
	while (tkn->type == TK_Pipe)
	{
		node = create_parent(TK_Pipe, node, NULL);
		tkn = tkn->next;
		parse_command(tkn, &node->rnode);
	}
	*nodeptr = node;
	return (tkn);
}

t_node	*parse(t_token *tkn)
{
	t_node	*node;

	tkn = parse_pipeline(tkn, &node);
	while ((tkn->type & GROUP_MASK) == GROUP3)
	{
		node = create_parent(tkn->type, node, NULL);
		tkn = tkn->next;
		parse_pipeline(tkn, &node->rnode);
	}
	return (node);
}
