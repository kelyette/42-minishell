/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:50:44 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/05 18:03:36 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# include "lexer.h"
# define STERRBADTKN "minishell: unexpected token '%s'\n"
# define STERREOL "minishell: unexpected end of line\n"

// error codes
// UEOL = unexpected end of line
enum	e_parse_error
{
	PE_OK,
	PE_BadTkn,
	PE_UEOL,
	PE_Internal
};

// node types inferred mostly from token types
enum	e_node_t
{
	NT_Candidate = 0,
	NT_Cmd = 1,
	NT_Assign = TK_Assign, // ---- 2
	NT_RdrIn = TK_In, // --------- 17
	NT_RdrOut = TK_Out, // ------- 18
	NT_RdrAppend = TK_Append, // - 19
	NT_HereDoc = TK_HereDoc, // -- 20
	NT_Pipe = TK_Pipe, // -------- 33
	NT_And = TK_And, // ---------- 49
	NT_Or = TK_Or, // ------------ 50
};

// TYPE     CHILDREN          DATA
// CMD      0                 command name and arguments
// Redir.   1 CMD             [number token] associated field
// Pipe     2 simple cmd      -
// Binary   2 pipelines       -
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

// node related
int		create_node(t_pctx *ctx, t_node **nodeptr, int type);
int		split_node(t_pctx *ctx, t_node **nodeptr, int type);
void	free_tree(t_node **rootptr);

// utils
void	print_err(t_pctx *ctx);
void	set_err(t_pctx *ctx, int type);
int		add_data(t_pctx *ctx, t_token **dataptr, t_token *val);
t_token	*lst_getlast_token(t_token *head);
int		in_group_tkn(int type, int group);

// dev functions TODO
void	print_tree(t_node *root);

#endif
