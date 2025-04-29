/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/29 15:42:27 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exe_assign(t_node *tree, int *ec, t_env *env)
{
	(void)tree;
	(void)ec;
	(void)env;
}

int	collect_cctx(t_cctx *ctx, t_node **treeptr, t_env *env)
{
	if (collect_redirs(&ctx->redir, treeptr))
		return (1);
	ctx->argv = lst_toarr_token((*treeptr)->data);
	ctx->envp = env_to_envp(&env);
	if (!ctx->argv)
		return (1);
	return (0);
}

void	exe_cmd(t_node *tree, int *ec, t_env *env) // TODO
{
	pid_t	pid;
	int		status;
	t_cctx	ctx;

	if (collect_cctx(&ctx, &tree, env))
		return ;
	if (!tree->data)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (perform_redirs(ctx.redir))
			return (perror("minishell1"));
		execve(ctx.argv[0], ctx.argv, ctx.envp);
		perror(ctx.argv[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	*ec = WEXITSTATUS(status);
	return ;
}
