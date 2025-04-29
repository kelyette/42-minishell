/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:51:36 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/29 15:47:25 by kcsajka          ###   ########.fr       */
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
char	**lst_toarr_token(t_token *head)
{
	char	**arr;
	size_t	size;
	int		i;

	if (!head)
		return (NULL);
	size = lst_getsize_token(head);
	arr = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (head)
	{
		arr[i++] = ft_strdup(head->str);
		head = head->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_arr(char **arr)
{
	while (*arr)
		free(arr);
}
