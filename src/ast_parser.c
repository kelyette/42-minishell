/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:19:27 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/15 14:46:37 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_node	*parse_command(t_pctx *ctx)
{
	t_node	*root;
	t_node	*cmdn;

	root = create_node(NT_Cmd);
	cmdn = root;
	while (ctx->tkn && (ctx->tkn->type & GROUP_MASK) <= GRP_REDIR)
	{
		if (ctx->tkn->type == TK_Assign && handle_assign(ctx, &root))
			return (free_tree(&root), NULL);
		if ((ctx->tkn->type & GROUP_MASK) == GRP_REDIR
			&& handle_redir(ctx, &root))
			return (NULL);
		if (ctx->tkn->type == TK_String)
			append_tkn_copy(ctx, &cmdn->data);
		ctx->tkn = ctx->tkn->next;
	}
	return (root);
}

t_node	*parse_pipeline(t_pctx *ctx)
{
	t_node	*root;

	root = parse_command(ctx);
	if (!root)
		return (1);
	while (tkn && tkn->type == TK_Pipe)
	{
		node = create_parent(TK_Pipe, node, NULL);
		tkn = parse_command(tkn->next, &node->rnode);
	}
	*nodeptr = node;
	return (tkn);
}

t_node	*parse_bin(t_pctx *ctx)
{
	t_node	*root;

	if (parse_pipeline())
	while (ctx->tkn && (ctx->tkn->type & GROUP_MASK) == GRP_BIN)
	{
		root = create_parent(tkn->type, root, NULL);
		if (!root)
			return (set_err(ctx, PE_Internal), NULL);
		if (parse_pipeline(tkn->next, &root->rnode))
			return (1);
	}
}

int	parse(t_token *tkn, t_node **rootptr)
{
	t_pctx	ctx;
	t_node	*root;

	root = parse_bin(ctx);
	if (ctx->err)
	return (0);
}