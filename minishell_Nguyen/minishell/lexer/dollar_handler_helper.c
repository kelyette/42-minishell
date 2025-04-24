/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 18:30:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (perror("Error"), NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	if ((*s1 || *s2) && n > 0)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

char	*ft_strjoin_variable(char *s1, char *s2, int i)
{
	char	*line;
	int		j;

	line = malloc(sizeof(char) * (i + ft_strlen(s2)) + 1);
	if (line == NULL)
		return (perror("Error"), NULL);
	j = 0;
	while (j < i)
	{
		line[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		line[j] = s2[i];
		j++;
		i++;
	}
	line[j] = '\0';
	return (line);
}
