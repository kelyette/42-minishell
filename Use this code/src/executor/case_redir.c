/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:00:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/09 14:37:51 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	collect_redirs(t_redir **headptr, t_node **treeptr)
{
	t_redir	*tmp;
	t_node	*tree;

	tree = *treeptr;
	*headptr = NULL;
	if (!in_group_tkn(tree->type, GRP_REDIR))
		return (0);
	while (tree && in_group_tkn(tree->type, GRP_REDIR))
	{
		tmp = malloc(sizeof(t_redir));
		tmp->next = *headptr;
		tmp->filename = tree->data->str;
		tmp->tfd = 0;
		if (tree->type == NT_RdrOut || tree->type == NT_RdrAppend)
			tmp->tfd = 1;
		if (tree->type == NT_RdrIn)
			tmp->flags = O_RDONLY;
		else if (tree->type == NT_RdrOut)
			tmp->flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (tree->type == NT_RdrAppend)
			tmp->flags = O_WRONLY | O_CREAT | O_APPEND;
		*headptr = tmp;
		tree = tree->lnode;
	}
	*treeptr = tree;
	return (0);
}

int	perform_redirs(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->flags & O_CREAT)
			fd = open(redir->filename, redir->flags, 0644);
		else
			fd = open(redir->filename, redir->flags);
		if (fd == -1)
			return (perror("minishell"), 1);
		if (dup2(fd, redir->tfd) == -1)
			return (perror("minishell"), 1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

/*void	exe_in(t_node *tree, int *ec, t_env *env)
{
	int		fd;

	fd = open(tree->data->str, O_RDONLY);
	if (fd == -1 || dup2(fd, 1))
		return (perror("minishell"));
	close(fd);
	executor(tree->lnode, ec, env);
	executor(tree->rnode, ec, env);
}

void	exe_out(t_node *tree, int *ec, t_env *env)
{
	executor(tree->lnode, ec, env);
	executor(tree->rnode, ec, env);
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
	else if (tree->type == NT_RdrAppend)
		exe_append(tree, ec, env);
}*/
