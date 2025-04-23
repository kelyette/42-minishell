/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:42:47 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/22 19:26:28 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// returns and consumes the curernt token if it is
// of type TK_Number, otherwise returns NULL
static t_token	*checkfd(t_pctx *ctx)
{
	t_token	*tmp;

	if (ctx->tkn->type != TK_Number)
		return (NULL);
	tmp = ctx->tkn;
	ctx->tkn = ctx->tkn->next;
	return (tmp);
}

// handles redirection operators
//  - check if the next token is valid
//  - create a parent redirection node
//  - copy relevant tokens to t_token *data
int	handle_redir(t_pctx *ctx, t_node **nodeptr)
{
	t_token	*expected;
	t_token	*fdtkn;

	fdtkn = checkfd(ctx);
	expected = ctx->tkn->next;
	if (!expected || expected->type == TK_Null)
		return (set_err(ctx, PE_UEOL), free_tree(nodeptr), 1);
	else if ((expected->type & GROUP_MASK) != GRP_SIMPLE)
		return (set_err(ctx, PE_BadTkn), free_tree(nodeptr), 1);
	if (expected->type == TK_Assign)
		expected->type = TK_String;
	if (split_node(ctx, nodeptr, ctx->tkn->type))
		return (free_tree(nodeptr), 1);
	if (fdtkn && add_data(ctx, &(*nodeptr)->data, fdtkn))
		return (free_tree(nodeptr), 1);
	if (add_data(ctx, &(*nodeptr)->data, expected))
		return (free_tree(nodeptr), 1);
	ctx->tkn = expected;
	return (0);
}

// handles assignment operators
// they will only be accepted as such if the command node is blank
// and has no other tokens in data than TK_Assign, otherwise
// they are converted to a string
int	handle_assign(t_pctx *ctx, t_node **nodeptr)
{
	t_token	*data;

	data = lst_getlast((*nodeptr)->data);
	if ((*nodeptr)->type != NT_Cmd || !data || data->type != TK_Assign)
		ctx->tkn->type = TK_String;
	else if (add_data(ctx, &(*nodeptr)->data, ctx->tkn))
		return (1);
	return (0);
}
