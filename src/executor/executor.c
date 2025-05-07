/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/01 20:58:35 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// From the root of the tree, recursively apply the executor
void	executor(t_node *tree, int *i, t_env **env)
{
	if (tree->type == NT_Candidate || tree == NULL)
		return ;
	else if (in_group_tkn(tree->type, GRP_BIN))
		exe_operator(tree, i, env);
	else if (in_group_tkn(tree->type, GRP_PIPE))
		exe_pipe(tree, i, env);
	else if (tree->type == NT_Cmd || in_group_tkn(tree->type, GRP_REDIR))
		exe_cmd(tree, i, env);
	else if (tree->type == NT_Assign)
		exe_assign(tree, i, env);
	/*else if (tree->type == NT_Expand)
		builtin_usd(tree, i, envp);*/
	return ;
}
