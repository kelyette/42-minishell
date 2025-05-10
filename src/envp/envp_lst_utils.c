/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:38 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/09 18:16:18 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// ENVP: free individual node
void	ft_lstdelone_env(t_env *lst)
{
	if (lst != NULL)
	{
		free(lst->key);
		free(lst->value);
		free(lst);
	}
}

// ENVP: clear and free the linked list
void	ft_lstclear_env(t_env **lst)
{
	t_env	*temp;

	if (*lst != NULL && lst != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			ft_lstdelone_env(*lst);
			*lst = temp;
		}
	}
}

// ENVP: add node to the back
void	ft_lstadd_back_env(t_env **lst, t_env *new_env)
{
	t_env	*temp;

	if (*lst == NULL)
		*lst = new_env;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_env;
	}
}

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
