/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:00:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 21:12:39 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	collect_redirs(t_redir **headptr, t_node **treeptr)
{
	t_redir	*tmp;
	t_node	*tree;

	tree = *treeptr;
	*headptr = NULL;
	if (!tree)
		return (0);
	if (!in_group_tkn(tree->type, GRP_REDIR))
		return (0);
	while (tree && in_group_tkn(tree->type, GRP_REDIR))
	{
		tmp = malloc(sizeof(t_redir));
		*tmp = (t_redir){tree->type, tree->data->str, 0, 0, -1, 0, *headptr};
		if (tree->type == NT_RdrOut || tree->type == NT_RdrAppend)
			tmp->tfd = 1;
		tmp->flags = get_rdr_flags(tree->type);
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
		free(line);
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
			return (close(redir->base_fd), perror(redir->filename), 1);
		if (dup2(fd, redir->tfd) == -1)
			return (close(redir->base_fd), perror(redir->filename), 1);
		close(fd);
		redir->active = 1;
		redir = redir->next;
	}
	return (0);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir);
		redir = tmp;
	}
}

void	reset_redirs(t_redir *redir)
{
	t_redir	*head;

	head = redir;
	while (redir)
	{
		if (redir->active)
		{
			if (redir->base_fd >= 0)
				if (dup2(redir->base_fd, redir->tfd) < 0)
					perror("minishell");
			close(redir->base_fd);
		}
		redir = redir->next;
	}
	free_redirs(head);
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
