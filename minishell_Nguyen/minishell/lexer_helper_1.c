/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:39:16 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/10 16:16:51 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	case_string_helper2(t_token **token, char *line, int *count)
{
	if (line[*count + 1] == '<' && line[*count + 2] == '<')
		(*token)->type = TK_Heredoc;
	else if (line[*count + 1] == '>' && line[*count + 2] == '>')
		(*token)->type = TK_Append;
	*count += 3;
}

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
void	ft_lstadd_back(t_token **lst, t_token *new_token)
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
	}
}

// copy the substring from the input
char	*ft_substring(char *s, int len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (len > 0)
	{
		ptr[i] = s[i];
		i++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
