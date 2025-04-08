/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:50:44 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/08 05:50:18 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"
# include "input.h"

enum	e_node_t
{
	NT_Candidate = 0,
	NT_Cmd = 1,
	NT_Expand = TK_USD,
	NT_Assign = TK_Assign,
	NT_RdrOut = TK_Out,
	NT_RdrAppn = TK_Append,
	NT_RdrIn = TK_In,
	NT_HereDoc = TK_HereDoc,
	NT_Pipe = TK_Pipe,
	NT_And = TK_And,
	NT_Or = TK_Or,
};

typedef struct s_args
{
	char	**argv;
	int		argc;
}	t_args;

union u_data
{
	t_args	*args;
	char	*field;
	t_token	*token;
};

typedef struct s_node
{
	int				type;
	struct s_node	*lnode;
	struct s_node	*rnode;
	union u_data	data;
}	t_node;

// parsing
t_node	*parse(t_token *tkn);

// node related
t_node	*create_node(int type);
t_node	*create_parent(int type, t_node *lchild, t_node *rchild);
void	free_tree(t_node *root);

// utils
t_token	*expect_token(t_token *tkn, int type);
int		append_tkn_copy(t_token *base, t_token *next);

#endif
