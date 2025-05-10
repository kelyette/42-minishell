/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:16:45 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/09 18:16:51 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

t_env	*get_env_key(const t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(key)))
			return ((t_env *)env);
		env = env->next;
	}
	return (NULL);
}

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
