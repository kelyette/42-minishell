/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:00:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/30 14:38:56 by kcsajka          ###   ########.fr       */
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
		*tmp = (t_redir){tree->type, tree->data->str, 0, 0, -1, *headptr};
		if (tree->type == NT_RdrOut || tree->type == NT_RdrAppend)
			tmp->tfd = 1;
		if (tree->type == NT_RdrIn)
			tmp->flags = O_RDONLY;
		else if (tree->type == NT_RdrOut)
			tmp->flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (tree->type == NT_RdrAppend)
			tmp->flags = O_WRONLY | O_CREAT | O_APPEND;
		else if (tree->type == NT_HereDoc)
			tmp->flags = O_WRONLY | O_CREAT | O_RDWR;
		*headptr = tmp;
		tree = tree->lnode;
	}
	*treeptr = tree;
	return (0);
}

int	handle_heredoc(t_redir *redir)
{
	int		fds[2];
	char	*line;
	char	*delim;
	int		dlen;

	delim = redir->filename;
	dlen = ft_strlen(delim);
	if (pipe(fds) < 0)
		return (perror("minishell"), -1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, delim, dlen) == 0
				&& (line[dlen] == '\n' || line[dlen] == 0)))
		{
			free(line);
			get_next_line(-1);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
	}
	close(fds[1]);
	return (fds[0]);
}

int	perform_redirs(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		redir->base_fd = dup(redir->tfd);
		if (redir->base_fd < 0)
			return (perror("minishell"), 1);
		if (redir->type == NT_HereDoc)
			fd = handle_heredoc(redir);
		else if (redir->type == NT_RdrOut || redir->type == NT_RdrAppend)
			fd = open(redir->filename, redir->flags, 0644);
		else
			fd = open(redir->filename, redir->flags);
		if (fd < 0)
			return (perror("minishell"), 1);
		if (dup2(fd, redir->tfd) == -1)
			return (perror("minishell"), 1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

void	reset_redirs(t_redir *redir)
{
	while (redir)
	{
		if (dup2(redir->base_fd, redir->tfd) < 0)
			perror("minishell");
		close(redir->base_fd);
	}
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
