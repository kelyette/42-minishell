/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:53:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/06/11 11:36:14 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	print_err(t_pctx *ctx)
{
	if (ctx->error == PE_OK)
		return ;
	else if (ctx->error == PE_UEOL || !ctx->tkn)
		ft_putendl_fd("syntax error near unexpected newline", 2);
	else if (ctx->error == PE_BadTkn)
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(ctx->tkn->str, 2);
	}
	else if (ctx->error == PE_Internal)
		perror("fatal: ");
	else
		ft_putendl_fd("error: unknown error code", 2);
}

inline void	set_err(t_pctx *ctx, int err)
{
	if (ctx->error == PE_OK)
		ctx->error = err;
}

t_token	*lst_getlast_token(t_token *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

// append a copy of val to the data pointer of a node
int	add_data(t_pctx *ctx, t_token **dataptr, t_token *val)
{
	t_token	*copy;
	t_token	*tmp;

	copy = malloc(sizeof(t_node));
	if (!copy)
		return (set_err(ctx, PE_Internal), 1);
	*copy = *val;
	copy->str = ft_strdup(val->str);
	copy->next = NULL;
	if (!*dataptr)
		*dataptr = copy;
	else
	{
		tmp = lst_getlast_token(*dataptr);
		tmp->next = copy;
	}
	return (0);
}

inline int	in_group_tkn(int type, int group)
{
	return ((type & GROUP_MASK) == group);
}

/*char	*tok2str(int type)
{
	switch (type)
	{
		case TK_Assign:
			return "=";
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
}*/
