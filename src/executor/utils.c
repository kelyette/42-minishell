/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:29:16 by kcsajka           #+#    #+#             */
/*   Updated: 2025/06/05 17:34:23 by kcsajka          ###   ########.fr       */
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
