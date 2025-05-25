/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:08:01 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/04 16:26:13 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*cur;

	(void)del;
	if (!lst)
		return (NULL);
	res = ft_lstnew((*f)(lst->content));
	lst = lst->next;
	cur = res;
	while (lst)
	{
		cur->next = ft_lstnew((*f)((lst)->content));
		cur = cur->next;
		lst = lst->next;
	}
	return (res);
}
