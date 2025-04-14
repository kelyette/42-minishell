/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:00:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/14 11:23:46 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	case_in(t_node *tree, int *i)
{
	/* code to change redirection input
	
	
	
	*/
	executor(tree->lnode, i);
	executor(tree->rnode, i);
}

void	case_out(t_node *tree, int *i)
{
	/* code to change redirection ouput
	
	
	
	*/
	executor(tree->lnode, i);
	executor(tree->rnode, i);
}

void	case_heredoc(t_node *tree, int *i)
{
	/* code to change redirection heredoc
	
	
	
	*/
	executor(tree->lnode, i);
	executor(tree->rnode, i);
}

void	case_append(t_node *tree, int *i)
{
	/* code to change redirection append
	
	
	
	*/
	executor(tree->lnode, i);
	executor(tree->rnode, i);
}

void	case_redirection(t_node *tree, int *i)
{
	if (tree->type == NT_RdrIn)
		case_in(tree, i);
	else if (tree->type == NT_HereDoc)
		case_heredoc(tree, i);
	else if (tree->type == NT_RdrOut)
		case_out(tree, i);
	else if (tree->type == NT_RdrAppn)
		case_append(tree, i);
}
