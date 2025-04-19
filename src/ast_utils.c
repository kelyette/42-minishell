/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:53:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/15 14:20:11 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	handle_err(enum e_parse_error err, t_node **rootptr, t_token *ctx)
{
	if (err == PE_OK)
		return (0);
	free_tree(rootptr);
	if (err == PE_BadTkn && (!ctx || !ctx->next))
		return (printf(STERREOL), 1);
	else
		return (printf(STERRBADTKN, ctx->next->str), 1);
	return (perror("fatal: "), err);
}

int	append_tkn_copy(t_pctx *ctx, t_token **head)
{
	t_token	*copy;
	t_token	*tmp;

	copy = malloc(sizeof(t_node));
	if (!copy)
		return (set_err(ctx, PE_Internal), 1);
	*copy = *ctx->tkn;
	copy->next = NULL;
	if (!*head)
		*head = copy;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = copy;
	}
	return (0);
}

inline t_pctx	*set_err(t_pctx *ctx, int err)
{
	ctx->error = err;
	return (ctx);
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
	if ((tree->type & GROUP_MASK) == GROUP1)
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