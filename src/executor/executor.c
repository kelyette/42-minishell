/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:26:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 17:01:36 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// From the root of the tree, recursively apply the executor
void	executor(t_node *tree, int *i, t_env *env)
{
	if (tree->type == NT_Candidate || tree == NULL)
		return ;
	else if (tree->type == NT_Or || tree->type == NT_And)
		exe_operator(tree, i, env);
	else if (tree->type == NT_Pipe)
		exe_pipe(tree, i, env);
	else if (tree->type == NT_RdrIn || tree->type == NT_HereDoc
		|| tree->type == NT_RdrOut || tree->type == NT_RdrAppn)
		exe_redirection(tree, i, env);
	else if (tree->type == NT_Assign)
		exe_assign(tree, i, env);
	/*else if (tree->type == NT_Expand)
		builtin_usd(tree, i, envp);*/
	else if (tree->type == NT_Cmd)
		exe_cmd(tree, i, env);
	return ;
}
