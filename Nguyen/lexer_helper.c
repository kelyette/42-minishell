/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:39:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/04 17:05:37 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// free individual node
void	ft_lstdelone(t_token *lst)
{
	if (lst != NULL)
	{
		free(lst->str);
		free(lst);
	}
}

// clear and free the linked list
void	ft_lstclear(t_token **lst)
{
	t_token	*temp;

	if (*lst != NULL && lst != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst);
			*lst = temp;
		}
	}
}

// add node to the back
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

// extract the substring, here extract the token from the input
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start + len > s_len)
		len = s_len - start;
	if (start >= s_len)
		len = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (len > 0)
	{
		ptr[i] = s[start + i];
		i++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
