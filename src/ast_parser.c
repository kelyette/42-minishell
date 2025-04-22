/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:19:27 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/22 17:46:44 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_node	*parse_cmd(t_pctx *ctx)
{
	t_node	*root;
	t_node	*cmd;

	if (!ctx->tkn || ctx->tkn->type == TK_Null)
		return (set_err(ctx, PE_UEOL), NULL);
	if (ctx->tkn->type > TK_In)
		return (set_err(ctx, PE_BadTkn), NULL);
	if (create_node(ctx, &cmd, NT_Cmd))
		return (NULL);
	root = cmd;
	while (ctx->tkn && (ctx->tkn->type & GROUP_MASK) <= GRP_REDIR)
	{
		if (ctx->tkn->type == TK_Assign
			&& handle_assign(ctx, &root))
			return (free_tree(&root), NULL);
		if ((ctx->tkn->type == TK_String || ctx->tkn->type == TK_USD)
			&& add_data(ctx, &cmd->data, ctx->tkn))
			return (free_tree(&root), NULL);
		if (((ctx->tkn->type & GROUP_MASK) == GRP_REDIR)
			&& handle_redir(ctx, &root))
			return (free_tree(&root), NULL);
		ctx->tkn = ctx->tkn->next;
	}
	return (root);
}

t_node	*parse_pipe(t_pctx *ctx)
{
	t_node	*root;

	root = parse_cmd(ctx);
	if (!root)
		return (NULL);
	while (ctx->tkn && ctx->tkn->type == TK_Pipe)
	{
		if (split_node(ctx, &root, TK_Pipe))
			return (NULL);
		ctx->tkn = ctx->tkn->next;
		root->rnode = parse_cmd(ctx);
		if (!root->rnode)
			return (set_err(ctx, PE_UEOL), free_tree(&root), NULL);
	}
	return (root);
}

t_node	*parse_bin(t_pctx *ctx)
{
	t_node	*root;

	root = parse_pipe(ctx);
	if (!root)
		return (NULL);
	while (ctx->tkn && (ctx->tkn->type & GROUP_MASK) == GRP_BIN)
	{
		if (split_node(ctx, &root, ctx->tkn->type))
			return (NULL);
		ctx->tkn = ctx->tkn->next;
		root->rnode = parse_pipe(ctx);
		if (!root->rnode)
			return (set_err(ctx, PE_UEOL), free_tree(&root), NULL);
	}
	return (root);
}

int	parse(t_token *head, t_node **rootptr)
{
	t_pctx	ctx;
	t_node	*root;

	*rootptr = NULL;
	ctx.tkn = head;
	ctx.error = PE_OK;
	root = parse_bin(&ctx);
	print_err(&ctx);
	if (ctx.error == PE_Internal)
		return (1);
	else if (ctx.error == PE_OK)
		*rootptr = root;
	return (0);
}
