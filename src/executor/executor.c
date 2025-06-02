/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/02 12:49:04 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// From the root of the tree, recursively apply the executor
int	executor(t_exec ex, t_node *tree)
{
	if (tree)
		ex.tree = tree;
	else if (ex.tree)
		tree = ex.tree;
	else
		tree = *ex.root;
	if (tree == NULL || tree->type == NT_Candidate)
		return (0);
	if (in_group_tkn(tree->type, GRP_BIN))
		return (exe_bin(ex));
	else if (in_group_tkn(tree->type, GRP_PIPE))
		return (exe_pipe(ex));
	else if (tree->type == NT_Cmd || in_group_tkn(tree->type, GRP_REDIR))
		return (set_get_code(exe_cmd(ex, DO_FORK), ex.env));
	else if (tree->type == NT_Assign)
		return (export_assign(tree->data->str, ex.env));
	/*else if (tree->type == NT_Expand)
		builtin_usd(tree, i, envp);*/
	return (0);
}
