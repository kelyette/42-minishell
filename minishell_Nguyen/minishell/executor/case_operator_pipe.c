/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_operator_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:29 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/14 12:16:28 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// This part is still to be defined
void	case_pipe(t_node *tree, int *i, char **envp)
{
	/*code to open pipe and change redirection to next pipe?
	
	
	
	
	*/
	executor(tree->lnode, i, envp);
	executor(tree->rnode, i, envp);
	// close pipe and reset redirection?
}

// Case of || and &&
void	case_operator(t_node *tree, int *i, char **envp)
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
