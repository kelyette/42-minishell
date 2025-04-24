/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 03:34:24 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exe_assign(t_node *tree, int *ec, t_env *env)
{
	(void)tree;
	(void)ec;
	(void)envp;
}

void	exe_cmd(t_node *tree, int *ec, t_env *env) // TODO
{
	t_ctx_cmd	ctx;
	pid_t		pid;
	int			status;

	if (collect_cmd(&ctx, tree->data) || collect_env)
		return (perror("minishell"));
	pid = fork();
	if (pid == 0)
	{
		char *argv[] = {"/usr/bin/diff", NULL};
		execve(argv[0], argv, ctx.envp);
		perror("minishell");
		exit(127);
	}
	waitpid(pid, &status, 0);
	*ec = WEXITSTATUS(status);
	return ;
}
