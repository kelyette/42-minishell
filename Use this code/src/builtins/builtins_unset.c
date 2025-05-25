/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:59:30 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/25 11:37:03 by hoannguy         ###   ########.fr       */
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
int	builtin_unset(t_node *node, t_env **env)
{
	t_env	*temp;

	if (env == NULL || *env == NULL || node->data == NULL)
		return (0);
	node->data = node->data->next;
	if (node->data == NULL)
		return (0);
	while (node->data != NULL)
	{
		temp = *env;
		while (temp != NULL)
		{
			if (!ft_strncmp(node->data->str, "?", 2))
				return (printf("Can not unset exit code\n"), 0);
			if (!ft_strncmp(node->data->str, temp->key,
					ft_compare(node->data->str, temp->key)))
			{
				pop_env(temp, env);
				break ;
			}
			temp = temp->next;
		}
		node->data = node->data->next;
	}
	return (0);
}
