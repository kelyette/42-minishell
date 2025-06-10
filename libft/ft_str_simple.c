/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:28:06 by kcsajka           #+#    #+#             */
/*   Updated: 2025/06/10 14:33:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	s;

	s = 0;
	while (str[s])
		s++;
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0)
		if (*s1++ != *s2++ || !s1[-1] || !s2[-1])
			return ((unsigned char)s1[-1] - (unsigned char)s2[-1]);
	return (0);
}
