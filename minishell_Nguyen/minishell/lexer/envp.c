/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:06 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/04 16:17:54 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

// update shlvl to reflect current shell level
// default behavior when executing shell in shell
int	update_shlvl(t_env **env)
{
	t_env	*temp;
	int		count;

	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp(temp->key, "SHLVL", 6))
		{
			count = ft_atoi(temp->value);
			free(temp->value);
			count += 1;
			temp->value = ft_itoa(count);
			if (temp->value == NULL)
				return (perror("Error"), ft_lstclear_env(env), 1);
			return (0);
		}
		temp = temp->next;
	}
	return (0);
}

int	initiate_exit_code(t_env **env)
{
	*env = malloc(sizeof(t_env));
	if (*env == NULL)
		return (perror("Error"), 1);
	(*env)->key = ft_strdup("?");
	if ((*env)->key == NULL)
		return (1);
	(*env)->value = ft_strdup("0");
	if ((*env)->value == NULL)
		return (perror("Error"), 1);
	(*env)->exported = false;
	(*env)->only_key = false;
	(*env)->code = true;
	(*env)->printed = false;
	(*env)->next = NULL;
	return (0);
}

// transform ARRAY envp to LIST env
int	transform_env(t_env **env, char **envp)
{
	t_env	*var;

	if (envp == NULL || *envp == NULL)
		return (initiate_base_env(env));
	if (initiate_exit_code(env) != 0)
		return (perror("Error"), 1);
	while (*envp != NULL)
	{
		var = malloc(sizeof(t_env));
		if (var == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->key = ft_substring_key(*envp);
		var->value = ft_substring_value(*envp);
		if (var->key == NULL || var->value == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->exported = true;
		var->only_key = false;
		var->code = false;
		var->printed = false;
		var->next = NULL;
		ft_lstadd_back_env(env, var);
		envp++;
	}
	return (update_shlvl(env));
}
