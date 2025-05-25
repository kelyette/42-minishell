/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:31:54 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/20 17:56:20 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		cn;
	int		slen;

	if (n == 0)
		return (ft_strdup("0"));
	cn = n;
	slen = (n < 0) + 1;
	while (n && slen++)
		n /= 10;
	res = malloc(slen);
	if (!res)
		return (NULL);
	res[--slen] = 0;
	if (cn < 0)
		*res = '-';
	while (cn)
	{
		res[--slen] = ft_abs(cn % 10) + '0';
		cn /= 10;
	}
	return (res);
}
