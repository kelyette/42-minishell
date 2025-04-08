/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:56:10 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/08 06:02:26 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

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

void	print_tree(t_node *tree)
{
	t_args	args;

	if (tree->type == NT_Cmd)
	{
		printf("CMD(");
		args = *tree->data.args;
		for (int i = 0; i < args.argc; i++)
			printf("%s%s", args.argv[i], i == args.argc - 1 ? ")\n" : ", ");
		return ;
	}
	printf("[%s", tok2str(tree->type));
	if (tree->lnode)
		print_tree(tree->lnode);
	if (tree->rnode)
		print_tree(tree->rnode);
	printf("]");
}

int	main(void)
{
	t_node			*tree;
	t_token	tokens[] = 
	{
		{ TK_String, "sort",       NULL },
		{ TK_In,     "<",          NULL },
		{ TK_String, "file.txt",   NULL },
		{ TK_And,    "&&",         NULL },
		{ TK_String, "echo",       NULL },
		{ TK_String, "done",       NULL },
		{ TK_Append, ">>",         NULL },
		{ TK_String, "output.txt", NULL },
		{ TK_Null,   NULL,         NULL }
	};
	for (int i = 0; tokens[i].type != TK_Null; i++) {
		tokens[i].next = &tokens[i + 1];
	}
	tree = parse(&tokens[0]);
	print_tree(tree);
}
