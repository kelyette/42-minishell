/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:29 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/23 17:20:51 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// This part is still to be defined
void	exe_pipe(t_node *tree, int *i, char **envp)
{
	/*code to open pipe and change redirection to next pipe?
	
	
	
	
	*/
	executor(tree->lnode, i, envp);
	executor(tree->rnode, i, envp);
	// close pipe and reset redirection?
}

// Case of || and &&
void	exe_operator(t_node *tree, int *i, char **envp)
{
	if (tree->type == NT_Or)
	{
		executor(tree->lnode, i, envp);
		if (*i != 0)
			executor(tree->rnode, i, envp);
		return ;
	}
	else if (tree->type == NT_And)
	{
		executor(tree->lnode, i, envp);
		if (*i == 0)
			executor(tree->rnode, i, envp);
		return ;
	}
}
