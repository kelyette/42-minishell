/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:50:44 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/15 14:18:40 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"
# include "input.h"
# define STERRBADTKN "minishell: unexpected token '%s'\n"
# define STERREOL "minishell: unexpected end of line\n"

enum	e_parse_error
{
	PE_OK,
	PE_BadTkn,
	PE_Internal
};

enum	e_node_t
{
	NT_Candidate = 0,
	NT_Cmd = 1,
	NT_RdrOut = TK_Out,
	NT_RdrAppn = TK_Append,
	NT_RdrIn = TK_In,
	NT_HereDoc = TK_HereDoc,
	NT_Pipe = TK_Pipe,
	NT_And = TK_And,
	NT_Or = TK_Or,
};

typedef struct s_node
{
	int				type;
	struct s_node	*lnode;
	struct s_node	*rnode;
	t_token			*data;
}	t_node;

typedef struct s_parse_ctx
{
	enum e_parse_error	error;
	t_token				*tkn;
}	t_pctx;

// parsing
int		parse(t_token *tkn, t_node **rootptr);
int		handle_redir(t_pctx *ctx, t_node **nodeptr);
int		handle_assign(t_pctx *ctx, t_node **nodeptr);
int		handle_string(t_pctx *ctx, t_node **nodeptr);

// node related
t_node	*create_node(int type);
t_node	*create_parent(int type, t_node *lchild, t_node *rchild);
void	free_tree(t_node **rootptr);

// utils
int		handle_err(t_pctx *ctx, enum e_parse_error err, t_node **rootptr);
t_pctx	*set_err(t_pctx *ctx, int err);
int		append_tkn_copy(t_pctx *ctx, t_token **head);

// dev functions TODO
void	print_tree(t_node *root);

#endif