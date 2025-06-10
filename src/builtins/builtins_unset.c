/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:59:30 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 16:53:54 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pop_env(t_env *temp, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp == temp)
	{
		*env = temp->next;
		ft_lstdelone_env(temp);
		return ;
	}
	while (tmp != NULL)
	{
		if (tmp->next == temp)
		{
			tmp->next = temp->next;
			ft_lstdelone_env(temp);
			return ;
		}
		tmp = tmp->next;
	}
}

// case unset, pop multiple variables
int	builtin_unset(t_node *node, t_env **env, t_exec ex)
{
	t_env	*temp;
	t_token	*current;

	(void)ex;
	if (!env || !*env || !node->data || !node->data->next)
		return (0);
	current = node->data->next;
	while (current != NULL)
	{
		temp = *env;
		while (temp != NULL)
		{
			if (!ft_strncmp(current->str, "?", 2))
				return (ft_putendl_fd("Can not unset exit code", 2), 0);
			if (!ft_strncmp(current->str, temp->key,
					ft_compare(current->str, temp->key)))
			{
				pop_env(temp, env);
				break ;
			}
			temp = temp->next;
		}
		current = current->next;
	}
	return (0);
}
