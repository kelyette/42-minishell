/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/29 13:03:28 by kcsajka          ###   ########.fr       */
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
# include "parser.h"

typedef struct s_redir
{
	char			*filename;
	int				tfd;
	int				flags;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmdctx
{
	t_redir	*redir;
	char	**argv;
	char	**envp;
}	t_cctx;

void	executor(t_node *tree, int *ec, t_env *env);
void	exe_operator(t_node *tree, int *ec, t_env *env);
void	exe_pipe(t_node *tree, int *ec, t_env *env);
void	exe_redirection(t_node *tree, int *ec, t_env *env);
void	exe_cmd(t_node *tree, int *ec, t_env *env);
void	exe_assign(t_node *tree, int *ec, t_env *env);

// exec utils
int		collect_redirs(t_redir **headptr, t_node **treeptr);
int		perform_redirs(t_redir *redir);

// utils
int		lst_getsize_token(t_token *head);
char	**lst_toarr_token(t_token *head);

#endif
