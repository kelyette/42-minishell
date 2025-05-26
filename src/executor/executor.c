/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/26 12:19:57 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// From the root of the tree, recursively apply the executor
int	executor(t_node *tree, t_env **env)
{
	if (tree == NULL || tree->type == NT_Candidate)
		return (0);
	else if (in_group_tkn(tree->type, GRP_BIN))
		return (exe_bin(tree, env));
	else if (in_group_tkn(tree->type, GRP_PIPE))
		return (exe_pipe(tree, env));
	else if (tree->type == NT_Cmd || in_group_tkn(tree->type, GRP_REDIR))
		return (set_get_code(exe_cmd(tree, env, DO_FORK), env));
	else if (tree->type == NT_Assign)
		return (export_assign(tree->data->str, env));
	/*else if (tree->type == NT_Expand)
		builtin_usd(tree, i, envp);*/
	return (0);
}
