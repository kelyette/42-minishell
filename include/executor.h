/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 17:10:06 by hoannguy         ###   ########.fr       */
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
# include "exec.h"
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
	int				type;
	char			*filename;
	int				tfd;
	int				flags;
	int				base_fd;
	int				active;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipeline
{
	t_node	**cmds;
	pid_t	*pids;
	int		(*fds)[2];
	int		size;
}	t_pipe;

int		executor(t_exec ex, t_node *tree);
int		exe_bin(t_exec ex);
int		exe_pipe(t_exec ex);
int		exe_cmd(t_exec ex, int can_fork);

// exec utils
int		collect_redirs(t_redir **headptr, t_node **treeptr);
int		perform_redirs(t_redir *redir);
int		search_bin_path(char **pathptr, t_env **env, char *name);
void	free_pid_cmd(t_pipe pl);
int		get_rdr_flags(int type);
int		collect_cmd_data(t_cmdd *cmdd, t_exec ex);
t_exec	newexec(t_exec ex, t_node *new);

void	reset_redirs(t_redir *redir);
void	free_redirs(t_redir *redir);
void	free_exec(t_exec ex);
void	free_cmdd(t_cmdd *cmdd);
void	clean_pipes(int (*fds)[2], int size);
void	close_pipe(int fd[2]);

// utils
int		lst_getsize_token(t_token *head);
char	**lst_toarr_token(t_token *head);
void	free_arr(char **arr);

#endif
