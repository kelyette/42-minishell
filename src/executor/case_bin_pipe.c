/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_bin_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:29 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/28 16:39:16 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	clean_pipes(int (*fds)[2], int size)
{
	int	i;

	i = -1;
	while (++i < size)
		close_pipe(fds[i]);
	free(fds);
}

int	collect_commands(t_node ***headptr, int *sizeptr, t_node *tree)
{
	t_node	**nodes;
	t_node	*tmp;
	int		i;

	tmp = tree;
	i = 0;
	while (tmp && tmp->type != NT_Cmd)
	{
		i += (tmp->lnode->type == NT_Cmd) + 1;
		tmp = tmp->lnode;
	}
	*sizeptr = i;
	nodes = malloc(sizeof(t_node *) * i);
	if (!nodes)
		return (perror("minishell"), 1);
	while (i > 0)
	{
		nodes[--i] = tree->rnode;
		if (tree->lnode->type == NT_Cmd)
			nodes[--i] = tree->lnode;
		tree = tree->lnode;
	}
	*headptr = nodes;
	return (0);
}

int	run_pipe_cmds(t_pipe pl, t_env **env)
{
	int	i;
	int	st;

	i = -1;
	while (++i < pl.size)
	{
		pl.pids[i] = fork();
		if (pl.pids[i] == -1)
			return (perror("minishell"), clean_pipes(pl.fds, pl.size), 1);
		if (pl.pids[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
    		signal(SIGQUIT, SIG_DFL);
			if (i > 0 && dup2(pl.fds[i - 1][0], STDIN_FILENO) == -1)
				return (perror("minishell"), exit(1), 1);
			if (i < pl.size - 1 && dup2(pl.fds[i][1], STDOUT_FILENO) == -1)
				return (perror("minishell"), exit(1), 1);
			clean_pipes(pl.fds, pl.size);
			int rval = exe_cmd(pl.cmds[i], env, NO_FORK);
			exit(rval);
		}
	}
	clean_pipes(pl.fds, pl.size);
	i = -1;
	while (++i < pl.size)
		waitpid(pl.pids[i], &st, 0);
	return (WEXITSTATUS(pl.pids[pl.size - 1]));
}

int	exe_pipe(t_node *tree, t_env **env)
{
	t_pipe	pl;
	int		i;

	if (collect_commands(&pl.cmds, &pl.size, tree))
		return (MS_ERROR);
	pl.fds = malloc(sizeof(int [2]) * pl.size);
	pl.pids = malloc(sizeof(pid_t) * pl.size);
	if (!pl.fds || !pl.pids)
		return (perror("minishell"), 1);
	i = -1;
	while (++i < pl.size)
		if (pipe(pl.fds[i]) == -1)
			return (perror("minishell"), clean_pipes(pl.fds, --i),
				free(pl.pids), MS_ERROR);
	if (run_pipe_cmds(pl, env))
		return (free(pl.cmds), free(pl.pids), MS_ERROR);
	return (free(pl.cmds), free(pl.pids), MS_OK);
}

/*// fd[0] read end, 1 write end
int	e1xe_pipe(t_node *tree, t_env **env)
{
	t_node	**cmds;
	pid_t	*pids;
	int		*sts;
	int		(*fds)[2];

	if (tree->type == NT_Cmd)
		return (exe_cmd(tree, env, NO_FORK));
	if (pipe(fd) == -1)
		return (1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (1);
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		exit(exe_pipe(tree->lnode, env));
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		exit(exe_cmd(tree->rnode, env, NO_FORK));
	}
	close_pipe(fd);
	waitpid(pid[0], &st[0], 0);
	waitpid(pid[1], &st[1], 0);
	return (WEXITSTATUS(st[1]));
}*/

// Case of || and &&
int	exe_bin(t_node *tree, t_env **env)
{
	if ((executor(tree->lnode, env) == 0) ^ (tree->type == NT_Or))
		executor(tree->rnode, env);
	return (0);
}
