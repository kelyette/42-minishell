/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:32:57 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/07 15:58:34 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*cb;

	cb = (char *)b;
	while (len--)
		*cb++ = c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void		*res;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	res = malloc(size * count);
	if (!res)
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
}
