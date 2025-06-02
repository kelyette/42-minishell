/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/02 18:33:46 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_cmdd(t_cmdd *cmdd)
{
	if (cmdd->envp)
		free_envp(cmdd->envp);
	if (cmdd->argv)
		free_arr(cmdd->argv);
	if (cmdd->path)
		free(cmdd->path);
	ft_bzero(cmdd, sizeof(*cmdd));
}

static int	collect_cmd_data(t_cmdd *cmdd, t_exec ex)
{
	cmdd->envp = env_to_envp(ex.env);
	cmdd->argv = lst_toarr_token(ex.tree->data);
	if (!cmdd->argv && ex.tree->data->str)
		return (free_envp(cmdd->envp), 1);
	cmdd->path = NULL;
	if (search_bin_path(&cmdd->path, ex.env, cmdd->argv[0]))
		return (free_cmdd(cmdd), 1);
	if (!cmdd->path)
		return (printf("minishell: %s: command not found\n", cmdd->argv[0]),
			free_cmdd(cmdd), 1);
	return (0);
}

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
	exit(MS_NO_EXEC);
}

int	exe_fork(t_exec ex, t_cmdd *cmdd, t_redir *redir)
{
	pid_t	pid;
	int		st;
	int		sig;

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
		exit(MS_NO_EXEC);
	}
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

int	exe_builtin(t_exec ex, t_bltnf builtinfn, t_redir *redir, int in_child)
{
	int	rval;

	if (perform_redirs(redir))
		return (MS_ERROR);
	rval = builtinfn(ex.tree, ex.env);
	reset_redirs(redir);
	free_redirs(redir);
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
		return (MS_ERROR);
	if (!ex.tree || !ex.tree->data)
		return (free_redirs(redir), MS_OK);
	builtinfn = lookup_builtin(ex.tree->data->str);
	if (builtinfn)
		return (set_get_code(exe_builtin(ex, builtinfn, redir,
					can_fork == NO_FORK), ex.env));
	rval = collect_cmd_data(&cmdd, ex);
	if (rval)
		return (free_redirs(redir), rval);
	if (can_fork == NO_FORK)
		rval = exe_nofork(ex, &cmdd, redir);
	else
		rval = exe_fork(ex, &cmdd, redir);
	return (free_cmdd(&cmdd), free_redirs(redir), set_get_code(rval, ex.env));
}
