/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:20:52 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/03 15:24:53 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*find_home(t_env **env)
{
	t_env	*temp;

	if (env == NULL || *env == NULL)
		return (NULL);
	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp("HOME", temp->key, 5))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*find_pwd(t_env **env)
{
	t_env	*temp;

	if (env == NULL || *env == NULL)
		return (NULL);
	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp("PWD", temp->key, 4))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*find_oldpwd(t_env **env)
{
	t_env	*temp;

	if (env == NULL || *env == NULL)
		return (NULL);
	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp("OLDPWD", temp->key, 7))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
