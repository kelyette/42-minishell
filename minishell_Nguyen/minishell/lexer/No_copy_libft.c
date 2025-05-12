/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   No_copy_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:07:51 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 22:28:00 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isnumber(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isprintable(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}

static int	check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ptr;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	j = ft_strlen(s1);
	while (i < j && s1[i] && check(s1[i], set) == 1)
		i++;
	while (j > i && check(s1[j - 1], set) == 1)
		j--;
	if (j == 0)
		i = 0;
	ptr = malloc(j - i + 1);
	if (ptr == NULL)
		return (NULL);
	k = 0;
	while (i < j)
		ptr[k++] = s1[i++];
	ptr[k] = '\0';
	return (ptr);
}

int	ft_isalphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

char	*malloc_itoa(long n, long count)
{
	char	*ptr;
	long	sign;

	sign = n;
	if (sign >= 0)
		ptr = malloc(sizeof(char) * (count + 1));
	if (sign < 0)
		ptr = malloc(sizeof(char) * (count + 2));
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

int	bit_count(long n)
{
	int		count;

	count = 0;
	if (n < 0)
		n = -n;
	if (n == 0)
		count = 1;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*exception(char *ptr)
{
	ptr[0] = '0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*ptr;
	long	i;

	i = n;
	count = bit_count(i);
	ptr = malloc_itoa(i, count);
	if (ptr == NULL)
		return (NULL);
	if (i == 0)
		ptr = exception(ptr);
	if (i < 0)
	{
		ptr[0] = '-';
		i = -i;
		count = count + 1;
	}
	ptr[count--] = '\0';
	while (i > 0)
	{
		ptr[count--] = i % 10 + '0';
		i = i / 10;
	}
	return (ptr);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	nb;

	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign = -sign;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	return (nb * sign);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
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

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
