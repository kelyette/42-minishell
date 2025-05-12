/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_helper_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:45:49 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/03 14:58:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

char	*exception(char *ptr)
{
	ptr[0] = '0';
	return (ptr);
}

int	initiate_base_env_helper(t_env **env)
{
	t_env	*shlvl;

	shlvl = malloc(sizeof(t_env));
	if (shlvl == NULL)
		return (perror("Error"), ft_lstclear_env(env), 1);
	shlvl->key = ft_strdup("SHLVL");
	if (shlvl->key == NULL)
		return (1);
	shlvl->value = ft_strdup("1");
	if (shlvl->value == NULL)
		return (1);
	shlvl->exported = true;
	shlvl->only_key = false;
	shlvl->code = false;
	shlvl->printed = false;
	shlvl->next = NULL;
	(*env)->next = shlvl;
	return (0);
}

// in case of NULL envp,
// initiate 2 environnement variables PWD and SHLVL
int	initiate_base_env(t_env **env)
{
	*env = malloc(sizeof(t_env));
	if (*env == NULL)
		return (perror("Error"), 1);
	(*env)->key = ft_strdup("PWD");
	if ((*env)->key == NULL)
		return (1);
	(*env)->value = getcwd(NULL, 0);
	if ((*env)->value == NULL)
		return (perror("Error"), 1);
	(*env)->exported = true;
	(*env)->only_key = false;
	(*env)->code = false;
	(*env)->printed = false;
	(*env)->next = NULL;
	return (initiate_base_env_helper(env));
}
