/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_helper_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:52:41 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/04 16:45:30 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
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
