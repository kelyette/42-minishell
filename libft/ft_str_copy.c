/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:21:24 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/07 16:34:38 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	while (dstsize && src[++i] && i < dstsize - 1)
		dst[i] = src[i];
	if (dstsize)
		dst[i] = 0;
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const size_t	srclen = ft_strlen(src);
	size_t			dstlen;
	size_t			i;

	if (!dstsize)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	dst += dstlen;
	i = -1;
	if (srclen < dstsize - dstlen)
		while (++i < srclen + 1)
			dst[i] = *src++;
	else
	{
		while (++i + dstlen < dstsize - 1)
			dst[i] = *src++;
		dst[i] = 0;
	}
	return (dstlen + srclen);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	res = malloc(ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i] = 0;
	return (res);
}
