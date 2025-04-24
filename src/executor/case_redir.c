/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:00:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 17:25:09 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exe_in(t_node *tree, int *i, t_env *env)
{
	char	*filename;
	int		fd[2];

	collect_redir(&filename, &fd[1], tree->data);
	fd[0] = open(filename, O_RDONLY);
	if (fd[0] == -1 || dup2(fd[0], fd[1]))
		return (perror("minishell"));
	executor(tree->lnode, i, env);
	executor(tree->rnode, i, env);
	// reset redirection?
}

void	exe_out(t_node *tree, int *i, t_env *env)
{
	executor(tree->lnode, i, env);
	executor(tree->rnode, i, env);
	// reset redirection?
}

void	exe_heredoc(t_node *tree, int *i, t_env *env)
{
	executor(tree->lnode, i, env);
	executor(tree->rnode, i, env);
	// reset redirection?
}

void	exe_append(t_node *tree, int *i, t_env *env)
{
	executor(tree->lnode, i, env);
	executor(tree->rnode, i, env);
	// reset redirection?
}

// This part is still to be defined
void	exe_redirection(t_node *tree, int *i, t_env *env)
{
	if (tree->type == NT_RdrIn)
		exe_in(tree, i, env);
	else if (tree->type == NT_HereDoc)
		exe_heredoc(tree, i, env);
	else if (tree->type == NT_RdrOut)
		exe_out(tree, i, env);
	else if (tree->type == NT_RdrAppn)
		exe_append(tree, i, env);
}
