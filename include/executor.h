/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/05 18:26:59 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/param.h>
# include "minishell.h"
# include "libft.h"
# include "envp.h"
# include "parser.h"

typedef int	(*t_bltnf)(t_node *node, t_env **env);
struct s_builtin
{
	char	*str;
	t_bltnf	fn;
};

typedef struct s_redir
{
	char			*filename;
	int				tfd;
	int				flags;
	struct s_redir	*next;
}	t_redir;

void	executor(t_node *tree, int *ec, t_env **env);
void	exe_operator(t_node *tree, int *ec, t_env **env);
void	exe_pipe(t_node *tree, int *ec, t_env **env);
//void	exe_redirection(t_node *tree, int *ec, t_env **env);
void	exe_cmd(t_node *tree, int *ec, t_env **env);
void	exe_assign(t_node *tree, int *ec, t_env **env);

// builtins
t_bltnf	lookup_builtin(char *name);
int		builtin_echo(t_node *node, t_env **env);
int		builtin_pwd(t_node *node, t_env **env);
int		builtin_env(t_node *node, t_env **env);
int		builtin_export(t_node *node, t_env **env);
int		builtin_cd(t_node *node, t_env **env);

// exec utils
int		collect_redirs(t_redir **headptr, t_node **treeptr);
int		perform_redirs(t_redir *redir);
char	*search_bin_path(const t_env *env, char *name);

// utils
int		lst_getsize_token(t_token *head);
char	**lst_toarr_token(t_token *head);
void	free_arr(char **arr);

#endif
