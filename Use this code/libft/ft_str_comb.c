/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_comb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:40:11 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/19 17:33:30 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	i;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < n && s1[i])
		res[i] = s1[i];
	res[i] = 0;
	return (res);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(size);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char const	*cs = (char *)s;
	char		**res;
	int			scount;
	size_t		slen;

	if (!s)
		return (NULL);
	scount = 0;
	while (*s)
		if (*s++ != c && (!*s || *s == c))
			scount++;
	res = malloc(sizeof(char *) * (scount + 1));
	if (!res)
		return (NULL);
	while (cs - s < 0)
	{
		slen = 0;
		while (cs[slen] && cs[slen] != c)
			slen++;
		if (slen > 0)
			*res++ = ft_strndup(cs, slen);
		cs += slen + 1;
	}
	*res = NULL;
	return (res - scount);
}

void	ft_free_split(char **split)
{
	char	**s;

	if (!split)
		return ;
	s = split;
	while (*split)
		free(*split++);
	free(s);
}
