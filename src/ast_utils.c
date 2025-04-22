/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:53:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/22 17:39:57 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	print_err(t_pctx *ctx)
{
	if (ctx->error == PE_OK)
		return ;
	else if (ctx->error == PE_UEOL || !ctx->tkn)
		printf(STERREOL);
	else if (ctx->error == PE_BadTkn)
		printf(STERRBADTKN, ctx->tkn->str);
	else if (ctx->error == PE_Internal)
		perror("fatal: ");
	else
		printf("error: unknown error code %d\n", ctx->error);
}

inline void	set_err(t_pctx *ctx, int err)
{
	if (ctx->error == PE_OK)
		ctx->error = err;
}

t_token	*lst_getlast(t_token *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

int	add_data(t_pctx *ctx, t_token **dataptr, t_token *val)
{
	t_token	*copy;
	t_token	*tmp;

	copy = malloc(sizeof(t_node));
	if (!copy)
		return (set_err(ctx, PE_Internal), 1);
	*copy = *val;
	copy->next = NULL;
	if (!*dataptr)
		*dataptr = copy;
	else
	{
		tmp = lst_getlast(*dataptr);
		tmp->next = copy;
	}
	return (0);
}

char	*tok2str(int type)
{
	switch (type)
	{
		case TK_Assign:
			return "=";
		case TK_USD:
			return "$";
		case TK_In:
			return "<";
		case TK_Out:
			return ">";
		case TK_HereDoc:
			return "<<";
		case TK_Append:
			return ">>";
		case TK_Pipe:
			return "|";
		case TK_And:
			return "&&";
		case TK_Or:
			return "||";
	}
	return ("???");
}

void	print_tree_helper(t_node *tree, int indent) // TODO remove dev function
{
	t_token	*args;

	if (!tree)
		return ;
	printf("%*s", indent * 2, "");
	if (tree->type == NT_Cmd)
	{
		printf("CMD(");
		args = tree->data;
		for (; args != NULL; args = args->next)
			printf("%s%s", args->str, args->next ? ", " : "");
		printf(")\n");
		return ;
	}
	if ((tree->type & GROUP_MASK) == GRP_REDIR)
		printf("%s \"%s\"\n", tok2str(tree->type), tree->data->str);
	else
		printf("%s\n", tok2str(tree->type));
	if (tree->lnode)
		print_tree_helper(tree->lnode, indent + 1);
	if (tree->rnode)
		print_tree_helper(tree->rnode, indent + 1);
}

void	print_tree(t_node *tree)
{
	print_tree_helper(tree, 0);
}

/* leave this part for the execution component
int	token2args(union u_data *dataptr)
{
	t_args	*args;
	t_token	*tkn;
	int		i;

	if (!dataptr->token)
		return (0);
	args = calloc(1, sizeof(t_args)); // TODO forbidden func
	args->name = tkn->str;
	args->argc = 0;
	while (tkn && ++args->argc)
		tkn = tkn->next;
	args->argv = malloc(args->argc * sizeof(t_token *));
	tkn = dataptr->token->next;
	i = 0;
	while (tkn)
	{
		args->argv[i++] = tkn->str;
		tkn = tkn->next;
	}
	dataptr->args = args;
	return (0);
}*/
