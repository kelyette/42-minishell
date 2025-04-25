/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:00:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/25 19:34:00 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exe_in(t_node *tree, int *ec, t_env *env)
{
	int		fd;

	fd = open(tree->data->str, O_RDONLY);
	if (fd == -1 || dup2(fd, 1))
		return (perror("minishell"));
	close(fd);
	executor(tree->lnode, ec, env);
	executor(tree->rnode, ec, env);
	// reset redirection?
}

void	exe_out(t_node *tree, int *ec, t_env *env)
{
	executor(tree->lnode, ec, env);
	executor(tree->rnode, ec, env);
	// reset redirection?
}

void	exe_heredoc(t_node *tree, int *ec, t_env *env)
{
	executor(tree->lnode, ec, env);
	executor(tree->rnode, ec, env);
	// reset redirection?
}

void	exe_append(t_node *tree, int *ec, t_env *env)
{
	executor(tree->lnode, ec, env);
	executor(tree->rnode, ec, env);
	// reset redirection?
}

// This part is still to be defined
void	exe_redirection(t_node *tree, int *ec, t_env *env)
{
	if (tree->type == NT_RdrIn)
		exe_in(tree, ec, env);
	else if (tree->type == NT_HereDoc)
		exe_heredoc(tree, ec, env);
	else if (tree->type == NT_RdrOut)
		exe_out(tree, ec, env);
	else if (tree->type == NT_RdrAppn)
		exe_append(tree, ec, env);
}
