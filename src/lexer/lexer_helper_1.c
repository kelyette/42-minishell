/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:39:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/04 12:32:48 by hoannguy         ###   ########.fr       */
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

int	is_valid_char(char c)
{
	if (c == '\0' || ft_isspace(c))
		return (0);
	if (c == '<' || c == '>' || c == '|')
		return (0);
	return (1);
}
