/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:31:13 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/03 14:29:20 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = -1;
	while (++i < n)
		((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*csrc;
	char	*cdst;

	if (!dst && !src)
		return (NULL);
	csrc = (char *)src;
	cdst = (char *)dst;
	i = -1;
	while (++i < n)
	{
		cdst[i] = csrc[i];
		if (csrc[i] == c)
			return (cdst);
	}
	return (NULL);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;

	if (!dst && !src)
		return (NULL);
	cdst = (char *)dst;
	csrc = (char *)src;
	if (dst <= src)
		while (len--)
			*cdst++ = *csrc++;
	else
	{
		cdst += len -1;
		csrc += len -1;
		while (len--)
			*cdst-- = *csrc--;
	}
	return (dst);
}
