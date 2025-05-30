/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/28 14:10:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <sys/errno.h>
# include "minishell.h"
# include "libft.h"
# include "envp.h"
# include "parser.h"
# include "builtins.h"
# define DO_FORK 1
# define NO_FORK 0

typedef struct s_cmd_data
{
	char	*path;
	char	**argv;
	char	**envp;
}	t_cmdd;

typedef struct s_redir
{
	char			*filename;
	int				tfd;
	int				flags;
	int				base_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipeline
{
	t_node	**cmds;
	pid_t	*pids;
	int		(*fds)[2];
	int		size;
}	t_pipe;

typedef struct s_exec
{
	t_node	**root;
	t_node	*tree;
	t_env	**env;
}	t_exec;

int		executor(t_node *tree, t_env **env);
int		exe_bin(t_node *tree, t_env **env);
int		exe_pipe(t_node *tree, t_env **env);
int		exe_cmd(t_node *tree, t_env **env, int can_fork);

// exec utils
int		collect_redirs(t_redir **headptr, t_node **treeptr);
int		perform_redirs(t_redir *redir);
void	reset_redirs(t_redir *redir);
void	free_redirs(t_redir *redir);
int		search_bin_path(char **pathptr, t_env **env, char *name);

// utils
int		lst_getsize_token(t_token *head);
char	**lst_toarr_token(t_token *head);
void	free_arr(char **arr);

#endif
