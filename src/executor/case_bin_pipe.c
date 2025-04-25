/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_bin_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:29 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/25 13:00:42 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// This part is still to be defined
void	exe_pipe(t_node *tree, int *i, t_env *env)
{
	/*code to open pipe and change redirection to next pipe?
	
	
	
	
	*/
	executor(tree->lnode, i, env);
	executor(tree->rnode, i, env);
	// close pipe and reset redirection?
}

// Case of || and &&
void	exe_operator(t_node *tree, int *i, t_env *env)
{
	executor(tree->lnode, i, env);
	if ((*i == 0) ^ (tree->type == NT_Or))
		executor(tree->rnode, i, env);
	return ;
}
