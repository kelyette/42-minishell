/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_operator_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:29 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/14 11:23:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	case_pipe(t_node *tree, int *i)
{
	/*code to open pipe and change redirection to next pipe
	
	
	
	
	*/
	executor(tree->lnode, i);
	executor(tree->rnode, i);
}

void	case_operator(t_node *tree, int *i)
{
	if (tree->type == NT_Or)
	{
		executor(tree->lnode, i);
		if (*i != 0)
			executor(tree->rnode, i);
		return ;
	}
	else if (tree->type == NT_And)
	{
		executor(tree->lnode, i);
		if (*i == 0)
			executor(tree->rnode, i);
		return ;
	}
}
