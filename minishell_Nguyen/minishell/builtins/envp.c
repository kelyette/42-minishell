/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:06 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/30 14:54:48 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

char	**env_to_envp_helper(char **envp, t_env *temp, int i)
{
	char	*tmp;

	envp[i] = NULL;
	tmp = ft_strjoin(temp->key, "=");
	if (tmp == NULL)
		return (free_envp(envp), NULL);
	envp[i] = ft_strjoin(tmp, temp->value);
	free(tmp);
	if (envp[i] == NULL)
		return (free_envp(envp), NULL);
	return (envp);
}

// transform LIST env to ARRAY envp
char	**env_to_envp(t_env **env)
{
	t_env	*temp;
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (ft_lstsize(*env) + 1));
	if (envp == NULL)
		return (perror("Error"), NULL);
	temp = *env;
	i = 0;
	while (temp != NULL)
	{
		if (temp->exported == true)
		{
			envp = env_to_envp_helper(envp, temp, i);
			if (envp == NULL)
				return (NULL);
			i++;
		}
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

// transform ARRAY envp to LIST env
int	transform_env(t_env **env, char **envp)
{
	t_env	*var;

	while (*envp != NULL)
	{
		var = malloc(sizeof(t_env));
		if (var == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->key = ft_substring_key(*envp);
		if (var->key == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->value = ft_substring_value(*envp);
		if (var->value == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->exported = true;
		var->only_key = false;
		var->code = false;
		var->printed = false;
		var->next = NULL;
		ft_lstadd_back_env(env, var);
		envp++;
	}
	return (0);
}
