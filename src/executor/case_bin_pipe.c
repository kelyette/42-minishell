/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_bin_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:29 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 04:03:00 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	collect_commands(t_node ***headptr, int *sizeptr, t_node *tree)
{
	t_node	**nodes;
	t_node	*tmp;
	int		i;

	tmp = tree;
	i = 0;
	while (tmp && tmp->type == NT_Pipe)
	{
		i += (tmp->lnode->type != NT_Pipe) + 1;
		tmp = tmp->lnode;
	}
	*sizeptr = i;
	nodes = malloc(sizeof(t_node *) * i);
	if (!nodes)
		return (perror("minishell"), 1);
	while (i > 0)
	{
		nodes[--i] = tree->rnode;
		if (tree->lnode->type != NT_Pipe)
			nodes[--i] = tree->lnode;
		tree = tree->lnode;
	}
	*headptr = nodes;
	return (0);
}

int	start_cmds(t_pipe pl, t_exec ex)
{
	int	i;
	int	ec;

	i = -1;
	while (++i < pl.size)
	{
		pl.pids[i] = fork();
		if (pl.pids[i] == -1)
			return (perror("minishell"), clean_pipes(pl.fds, pl.size - 1), 1);
		if (pl.pids[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (i > 0 && dup2(pl.fds[i - 1][0], STDIN_FILENO) == -1)
				return (perror("minishell"), free_exec(ex), exit(1), 1);
			if (i < pl.size - 1 && dup2(pl.fds[i][1], STDOUT_FILENO) == -1)
				return (perror("minishell"), free_exec(ex), exit(1), 1);
			clean_pipes(pl.fds, pl.size - 1);
			ex.tree = pl.cmds[i];
			ec = exe_cmd(ex, NO_FORK);
			free_pid_cmd(pl);
			exit(ec);
		}
	}
	return (0);
}

int	wait_cmds(t_pipe pl)
{
	int	i;
	int	sig;
	int	st;
	int	ec;

	i = -1;
	while (++i < pl.size)
	{
		waitpid(pl.pids[i], &st, 0);
		if (WIFSIGNALED(st))
		{
			sig = WTERMSIG(st);
			if (sig == SIGINT)
				printf("\n");
			if (sig == SIGQUIT)
				printf("Quit (core dumped)\n");
			ec = 128 + sig;
		}
		else if (i == pl.size - 1 && WIFEXITED(st))
			ec = WEXITSTATUS(st);
	}
	return (ec);
}

int	run_pipe_cmds(t_pipe pl, t_exec ex)
{
	int	ec;

	disable_sigint_handler();
	ec = start_cmds(pl, ex);
	if (ec)
		return (ec);
	clean_pipes(pl.fds, pl.size - 1);
	ec = wait_cmds(pl);
	restore_sigint_handler();
	return (ec);
}

int	exe_pipe(t_exec ex)
{
	t_pipe	pl;
	int		i;
	int		rval;

	if (collect_commands(&pl.cmds, &pl.size, ex.tree))
		return (MS_ERROR);
	pl.fds = malloc(sizeof(int [2]) * (pl.size - 1));
	pl.pids = malloc(sizeof(pid_t) * pl.size);
	if (!pl.fds || !pl.pids)
		return (free(pl.cmds), perror("minishell"), 1);
	i = -1;
	while (++i < pl.size - 1)
		if (pipe(pl.fds[i]) == -1)
			return (perror("minishell"), clean_pipes(pl.fds, i),
				free(pl.pids), MS_ERROR);
	rval = run_pipe_cmds(pl, ex);
	return (free(pl.cmds), free(pl.pids), rval);
}
