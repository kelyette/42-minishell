/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:11:29 by hoannguy          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/05/28 17:23:35 by hoannguy         ###   ########.fr       */
=======
/*   Updated: 2025/05/28 14:16:13 by kcsajka          ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// create new env variable
int	new_assign(char *key, char *value, t_env **env)
{
	t_env	*var;

	var = malloc(sizeof(t_env));
	if (var == NULL)
		return (perror("Error"), 1);
	var->key = key;
	var->value = value;
	var->exported = true;
	var->only_key = false;
	var->code = false;
	var->printed = false;
	ft_lstadd_back_env(env, var);
	return (0);
}

// case export follow by assign, like export test=
// if test exist, update the value
// if test doesn't exist, create new env variable
int	export_assign(char *s, t_env **env)
{
	char	*key;
	char	*value;
	t_env	*temp;

	key = ft_substring_key(s);
	if (key == NULL)
		return (perror("Error"), 1);
	value = ft_substring_value(s);
	if (value == NULL)
		return (perror("Error"), free(key), 1);
	temp = *env;
	while (temp != NULL)
	{
		if (ft_strlen(key) == ft_strlen(temp->key)
			&& ft_strncmp(key, temp->key, ft_strlen(key)) == 0)
		{
			temp->exported = true;
			temp->only_key = false;
			free(temp->value);
			temp->value = value;
			free(key);
			return (0);
		}
		temp = temp->next;
	}
	return (new_assign(key, value, env));
}

// case export follow by a string, like export a
// if a existe, export it
// if a doesn't exist, put it in linked list but not export
int	export_string(char *key, t_env **env)
{
	t_env	*temp;
	t_env	*var;

	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp(key, temp->key, ft_strlen(key)) && temp->code == false)
		{
			temp->exported = true;
			return (0);
		}
		temp = temp->next;
	}
	var = malloc(sizeof(t_env));
	if (var == NULL)
		return (perror("Error"), 1);
	var->key = ft_strdup(key);
	var->value = ft_strdup("");
	if (var->key == NULL || var->value == NULL)
		return (perror("Error"), 1);
	var->exported = false;
	var->only_key = true;
	var->code = false;
	ft_lstadd_back_env(env, var);
	return (0);
}

// case export
int	builtin_export(t_node *node, t_env **env)
{
	if (env == NULL && *env == NULL)
		return (0);
	if (node->data->next == NULL)
		return (export_no_arg(env));
	else
	{
		node->data = node->data->next;
		if (node->data->type == TK_Assign || ft_strchr(node->data->str, '='))
		{
			return (export_assign(node->data->str, env));
		}
		else if (node->data->type == TK_String)
		{
			return (export_string(node->data->str, env));
		}
	}
	return (0);
}
