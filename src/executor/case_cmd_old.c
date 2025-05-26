/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_cmd_old.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 16:59:48 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// calls builtin commands or replaces the current process with the command
// specified in tree->data. no forks are made here.
int	exec_process(t_node *tree, t_redir *redir, t_env **env, int do_fork)
{
	t_bltnf	builtinfn;
	char	*path;
	char	**argv;
	char	**envp;

	if (!tree || !tree->data)
		return (0);
	perform_redirs(tree);
	builtinfn = lookup_builtin(tree->data->str);
	if (builtinfn)
		return (builtinfn(tree, env));
	
	return (0);
}

int	exe_cmd(t_node *tree, t_)

int	exec_bin(t_node *tree, t_redir *redir, const t_env *env)
{
	pid_t	pid;
	int		st;
	char	*path;
	char	**argv;
	char	**envp;

	envp = env_to_envp((t_env **)&env);
	argv = lst_toarr_token(tree->data);
	if (!argv)
		return (free_arr(envp), 1);
	path = search_bin_path(env, argv[0]);
	if (!path)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (perform_redirs(redir))
			return (perror("minishell"), 1);
		execve(path, argv, envp);
		perror(path);
		free(path);
		exit(127);
	}
	waitpid(pid, &st, 0);
	return (WEXITSTATUS(st));
}

int	exe_cmd(t_node *tree, t_env **env, int can_fork)
{
	t_redir	*redir;
	t_bltnf	builtinfn;

	if (collect_redirs(&redir, &tree))
		return (1);
	if (!tree || !tree->data)
		return ;
	builtinfn = lookup_builtin(tree->data->str);
	if (builtinfn)
	{
		if (perform_redirs(redir))
			return ;
		*ec = builtinfn(tree, env);
		return ;
	}
	
	*ec = exec_bin(tree, redir, *env);
	return ;
}
