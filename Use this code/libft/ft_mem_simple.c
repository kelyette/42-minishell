/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:34:03 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/03 14:09:05 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;

	if (n < 1)
		return (0);
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (n-- > 0)
		if (*cs1++ != *cs2++)
			return (cs1[-1] - cs2[-1]);
	return (0);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*cs;
	size_t	i;

	cs = (char *)s;
	i = -1;
	while (++i < n)
		if (cs[i] == (char)c)
			return (&cs[i]);
	return (NULL);
}
