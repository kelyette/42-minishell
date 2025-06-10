/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 21:01:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exe_nofork(t_exec ex, t_cmdd *cmdd, t_redir *redir)
{
	if (perform_redirs(redir))
	{
		free_exec(ex);
		exit(MS_ERROR);
	}
	execve(cmdd->path, cmdd->argv, cmdd->envp);
	perror(cmdd->argv[0]);
	free_exec(ex);
	free(cmdd->path);
	free_envp(cmdd->envp);
	exit(MS_NO_EXEC);
}

int	wait_fork(pid_t pid)
{
	int	st;
	int	sig;

	waitpid(pid, &st, 0);
	restore_sigint_handler();
	if (WIFSIGNALED(st))
	{
		sig = WTERMSIG(st);
		if (sig == SIGINT)
			printf("\n");
		if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		return (128 + sig);
	}
	return (WEXITSTATUS(st));
}

int	exe_fork(t_exec ex, t_cmdd *cmdd, t_redir *redir)
{
	pid_t	pid;

	disable_sigint_handler();
	pid = fork();
	if (pid < 0)
		return (perror("minishell"), MS_ERROR);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (perform_redirs(redir))
			exit(MS_ERROR);
		execve(cmdd->path, cmdd->argv, cmdd->envp);
		perror(cmdd->argv[0]);
		free_exec(ex);
		free(cmdd->path);
		free_envp(cmdd->envp);
		exit(MS_NO_EXEC);
	}
	return (wait_fork(pid));
}

int	exe_builtin(t_exec ex, t_bltnf builtinfn, t_redir *redir, int in_child)
{
	int	rval;

	if (perform_redirs(redir))
		return (reset_redirs(redir), MS_ERROR);
	rval = builtinfn(ex.tree, ex.env, ex);
	reset_redirs(redir);
	if (in_child)
		free_exec(ex);
	return (rval);
}

int	exe_cmd(t_exec ex, int can_fork)
{
	t_redir	*redir;
	t_bltnf	builtinfn;
	t_cmdd	cmdd;
	int		rval;

	if (collect_redirs(&redir, &ex.tree))
		return (reset_redirs(redir), MS_ERROR);
	if (!ex.tree || !ex.tree->data)
		return (perform_redirs(redir), reset_redirs(redir), MS_OK);
	builtinfn = lookup_builtin(ex.tree->data->str);
	if (builtinfn)
		return (exe_builtin(ex, builtinfn, redir, can_fork == NO_FORK));
	rval = collect_cmd_data(&cmdd, ex);
	if (rval)
		return (free_redirs(redir), rval);
	if (can_fork == NO_FORK)
		rval = exe_nofork(ex, &cmdd, redir);
	else
		rval = exe_fork(ex, &cmdd, redir);
	return (free_cmdd(&cmdd), free_redirs(redir), set_get_code(rval, ex.env));
}
