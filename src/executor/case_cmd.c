/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/26 15:10:43 by kcsajka          ###   ########.fr       */
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

static int	collect_cmd_data(t_cmdd *cmdd, t_node *tree, t_env **env)
{
	cmdd->envp = env_to_envp(env);
	cmdd->argv = lst_toarr_token(tree->data);
	if (!cmdd->argv && tree->data->str)
		return (free_envp(cmdd->envp), 1);
	cmdd->path = NULL;
	if (search_bin_path(&cmdd->path, env, cmdd->argv[0]))
		return (free_cmdd(cmdd), 1);
	if (!cmdd->path)
		return (printf("minishell: %s: command not found\n", cmdd->argv[0]),
			free_cmdd(cmdd), 1);
	return (0);
}

int	exe_nofork(t_cmdd *cmdd, t_redir *redir)
{
	if (perform_redirs(redir))
		exit(MS_ERROR);
	execve(cmdd->path, cmdd->argv, cmdd->envp);
	perror(cmdd->argv[0]);
	exit(MS_NO_EXEC);
}

int	exe_fork(t_cmdd *cmdd, t_redir *redir)
{
	pid_t	pid;
	int		st;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), MS_ERROR);
	if (pid == 0)
	{
		if (perform_redirs(redir))
			exit(MS_ERROR);
		execve(cmdd->path, cmdd->argv, cmdd->envp);
		perror(cmdd->argv[0]);
		exit(MS_NO_EXEC);
	}
	waitpid(pid, &st, 0);
	return (WEXITSTATUS(st));
}

int	exe_cmd(t_node *tree, t_env **env, int can_fork)
{
	t_redir	*redir;
	t_bltnf	builtinfn;
	t_cmdd	cmdd;
	int		rval;

	if (collect_redirs(&redir, &tree))
		return (MS_ERROR);
	if (!tree || !tree->data)
		return (free_redirs(redir), MS_OK);
	builtinfn = lookup_builtin(tree->data->str);
	if (builtinfn)
	{
		if (perform_redirs(redir))
			return (MS_ERROR);
		rval = builtinfn(tree, env);
		return (reset_redirs(redir), free_redirs(redir), rval);
	}
	rval = collect_cmd_data(&cmdd, tree, env);
	if (rval)
		return (free_redirs(redir), rval);
	if (can_fork == NO_FORK)
		rval = exe_nofork(&cmdd, redir);
	else
		rval = exe_fork(&cmdd, redir);
	return (free_cmdd(&cmdd), free_redirs(redir), rval);
}
