/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/06 14:04:48 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exe_assign(t_node *tree, int *ec, t_env **env)
{
	(void)tree;
	(void)ec;
	(void)env;
}

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

void	exe_cmd(t_node *tree, int *ec, t_env **env)
{
	t_redir	*redir;
	t_bltnf	builtinfn;

	if (collect_redirs(&redir, &tree))
		return ;
	if (!tree || !tree->data)
		return ;
	builtinfn = lookup_builtin(tree->data->str);
	if (builtinfn)
	{
		if (perform_redirs(redir))
			return ;
		*ec = builtinfn(tree, env);
	}
	else
		*ec = exec_bin(tree, redir, *env);
	return ;
}
