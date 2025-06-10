/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:29:16 by kcsajka           #+#    #+#             */
/*   Updated: 2025/06/10 04:10:09 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_exec	newexec(t_exec ex, t_node *new)
{
	if (new)
		ex.tree = new;
	else if (!ex.tree)
		ex.tree = *ex.root;
	return (ex);
}

void	free_exec(t_exec ex)
{
	if (ex.root)
		free_tree(ex.root);
	if (ex.env)
		ft_lstclear_env(ex.env);
}

int	get_rdr_flags(int type)
{
	if (type == NT_RdrIn)
		return (O_RDONLY);
	else if (type == NT_RdrOut)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == NT_RdrAppend)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (0);
}

void	free_cmdd(t_cmdd *cmdd)
{
	if (cmdd->envp)
		free_envp(cmdd->envp);
	if (cmdd->argv)
		free_arr(cmdd->argv);
	if (cmdd->path)
		free(cmdd->path);
	ft_bzero(cmdd, sizeof(*cmdd));
}

int	collect_cmd_data(t_cmdd *cmdd, t_exec ex)
{
	int	code;

	cmdd->envp = env_to_envp(ex.env);
	cmdd->argv = lst_toarr_token(ex.tree->data);
	if (!cmdd->argv && ex.tree->data->str)
		return (free_envp(cmdd->envp), 1);
	cmdd->path = NULL;
	code = search_bin_path(&cmdd->path, ex.env, cmdd->argv[0]);
	if (code != 0)
		return (free_cmdd(cmdd), code);
	return (0);
}
