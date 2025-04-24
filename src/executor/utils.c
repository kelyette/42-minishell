/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:51:36 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/24 16:01:30 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	lst_getsize_token(t_token *head)
{
	int	i;

	i = 0;
	while (head && ++i)
		head = head->next;
	return (i);
}

// copies each string in a t_token* list to a null terminated char*[]
// only up to n values (-1 means no limit, 0 returns NULL)
char	**lst_toarr_token(t_token *head, int n)
{
	char	**arr;
	int		size;
	int		i;

	if (!head || !n)
		return (NULL);
	size = lst_getsize_token(head);
	if (size > n)
		size = n;
	arr = malloc(sizeof(char *) * size);
	i = 0;
	while (head && (n == -1 || i < n))
	{
		arr[i++] = ft_strdup(head->str);
		head = head->next;
	}
	return (arr);
}
