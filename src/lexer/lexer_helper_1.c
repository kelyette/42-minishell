/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:39:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/28 17:31:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// TOKEN: free individual node
void	ft_lstdelone_token(t_token *lst)
{
	if (lst != NULL)
	{
		free(lst->str);
		free(lst);
	}
}

// TOKEN: clear and free the linked list
void	ft_lstclear_token(t_token **lst)
{
	t_token	*temp;

	if (*lst != NULL && lst != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			ft_lstdelone_token(*lst);
			*lst = temp;
		}
	}
}

// TOKEN: add node to the back
void	ft_lstadd_back_token(t_token **lst, t_token *new_token)
{
	t_token	*temp;

	if (*lst == NULL)
		*lst = new_token;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
		new_token->next = NULL;
	}
}
