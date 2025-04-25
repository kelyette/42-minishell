/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:19:27 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/25 18:37:03 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// parse a "simple" command composed of strings, assignments,
// variables or redirection operators
static t_node	*parse_cmd(t_pctx *ctx)
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
		if (ctx->tkn->type == TK_Assign && handle_assign(ctx, &root))
			return (free_tree(&root), NULL);
		if ((ctx->tkn->type == TK_String)
			&& add_data(ctx, &cmd->data, ctx->tkn))
			return (free_tree(&root), NULL);
		if (((ctx->tkn->type & GROUP_MASK) == GRP_REDIR)
			&& handle_redir(ctx, &root))
			return (free_tree(&root), NULL);
		ctx->tkn = ctx->tkn->next;
	}
	if (cmd == root && !cmd->data)
		return (free(root), set_err(ctx, PE_BadTkn), NULL);
	return (root);
}

// parse pipes and commands within
static t_node	*parse_pipe(t_pctx *ctx)
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

// parse binary operators and pipelines within
static t_node	*parse_bin(t_pctx *ctx)
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

// parse tokens into a tree
// works by recursively calling sub parsing functions for operators
// with a precedence one level lower than the current one
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
