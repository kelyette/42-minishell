/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 03:33:03 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "minishell.h"
# include "libft.h"
# include "envp.h"
# include "ast.h"

typedef struct s_ctx_command
{
	char	**argv;
	char	**assign;
	char	**envp;
}	t_ctx_cmd;

void	executor(t_node *tree, int *ec, t_env *env);
void	exe_operator(t_node *tree, int *ec, t_env *env);
void	exe_pipe(t_node *tree, int *ec, t_env *env);
void	exe_redirection(t_node *tree, int *ec, t_env *env);
void	exe_cmd(t_node *tree, int *ec, t_env *env);
void	exe_assign(t_node *tree, int *ec, t_env *env);

// collectors
int		collect_cmdctx(t_ctx_cmd *ctx, t_token *data, t_env *env);
int		collect_redir(char **strptr, int *fdptr, t_token *data);
int		collect_envp(char ***envpptr, t_env *env);

// utils
int		lst_getsize_token(t_token *head);
char	**lst_toarr_token(t_token *head, int n);

#endif
