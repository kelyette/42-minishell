/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:13:55 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/28 17:31:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envp.h"

t_env	*initiate_pwd_env(t_env **env)
{
	t_env	*oldpwd;

	oldpwd = malloc(sizeof(t_env));
	if (oldpwd == NULL)
		return (perror("Error"), set_get_code(1, env), NULL);
	oldpwd->key = ft_strdup("PWD");
	if (oldpwd->key == NULL)
		return (set_get_code(1, env), NULL);
	oldpwd->value = getcwd(NULL, 0);
	if (oldpwd->value == NULL)
		return (perror("Error"), set_get_code(1, env), NULL);
	oldpwd->exported = true;
	oldpwd->only_key = false;
	oldpwd->code = false;
	oldpwd->printed = false;
	oldpwd->next = NULL;
	ft_lstadd_back_env(env, oldpwd);
	return (set_get_code(0, env), oldpwd);
}

t_env	*initiate_oldpwd_env(t_env **env)
{
	t_env	*oldpwd;

	oldpwd = malloc(sizeof(t_env));
	if (oldpwd == NULL)
		return (perror("Error"), set_get_code(1, env), NULL);
	oldpwd->key = ft_strdup("OLDPWD");
	if (oldpwd->key == NULL)
		return (set_get_code(1, env), NULL);
	oldpwd->value = NULL;
	oldpwd->exported = true;
	oldpwd->only_key = false;
	oldpwd->code = false;
	oldpwd->printed = false;
	oldpwd->next = NULL;
	ft_lstadd_back_env(env, oldpwd);
	return (set_get_code(0, env), oldpwd);
}

t_env	*get_env_key(t_env **env, char *key)
{
	t_env	*temp;

	if (env == NULL || *env == NULL)
		return (NULL);
	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp(key, temp->key, 5))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
