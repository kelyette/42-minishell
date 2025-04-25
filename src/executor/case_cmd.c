/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/25 19:35:01 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exe_assign(t_node *tree, int *ec, t_env *env)
{
	(void)tree;
	(void)ec;
	(void)env;
}

void	exe_cmd(t_node *tree, int *ec, t_env *env) // TODO
{
	pid_t		pid;
	int			status;
	char		**argv;
	char		**envp;

	if (!tree->data)
		return ;
	argv = lst_toarr_token(tree->data);
	envp = env_to_envp(&env);
	if (!argv || (env && !envp))
		return (perror("minishell"));
	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, envp);
		perror(argv[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	*ec = WEXITSTATUS(status);
	return ;
}
