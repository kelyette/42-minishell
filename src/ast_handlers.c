/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:42:47 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/15 14:17:29 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	handle_redir(t_pctx *ctx, t_node **nodeptr)
{
	t_node	*root;
	t_token	*expected;

	root = create_parent(ctx->tkn->type, *nodeptr, NULL);
	if (!root)
		return (set_err(ctx, PE_Internal), 1);
	expected = ctx->tkn->next;
	if (!expected || expected->type != TK_String || expected->type != TK_Assign)
		return (set_err(ctx, PE_BadTkn), free_tree(nodeptr), 1);
	if (expected->type == TK_Assign)
		expected->type = TK_String;
	root->data = expected;
	ctx->tkn = expected;
	return (0);
}

int	handle_assign(t_pctx *ctx, t_node **nodeptr)
{
	if ((*nodeptr)->type != NT_Cmd
		|| ((*nodeptr)->data && (*nodeptr)->data->type != TK_Assign))
	{
		ctx->tkn->type = TK_String;
		return (0);
	}
	if (append_tkn_copy(ctx, &(*nodeptr)->data))
		return (1);
	return (0);
}