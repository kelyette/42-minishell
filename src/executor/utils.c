/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:29:16 by kcsajka           #+#    #+#             */
/*   Updated: 2025/06/02 18:37:39 by kcsajka          ###   ########.fr       */
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
}
