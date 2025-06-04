/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/04 17:11:27 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// From the root of the tree, recursively apply the executor
int	executor(t_exec ex, t_node *tree)
{
	int	rval;

	if (tree)
		ex.tree = tree;
	else if (ex.tree)
		tree = ex.tree;
	else
		tree = *ex.root;
	if (tree == NULL || tree->type == NT_Candidate)
		return (0);
	rval = 0;
	if (in_group_tkn(tree->type, GRP_BIN))
		rval = exe_bin(ex);
	else if (in_group_tkn(tree->type, GRP_PIPE))
		rval = exe_pipe(ex);
	else if (tree->type == NT_Cmd || in_group_tkn(tree->type, GRP_REDIR))
		rval = exe_cmd(ex, DO_FORK);
	else if (tree->type == NT_Assign)
		rval = export_assign(tree->data->str, ex.env);
	return (set_get_code(rval, ex.env), rval);
}
