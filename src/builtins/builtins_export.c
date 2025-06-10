/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:11:29 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 16:54:45 by hoannguy         ###   ########.fr       */
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
			return (free(key), 0);
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

int	argument_checker(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

// case export
int	builtin_export(t_node *node, t_env **env, t_exec ex)
{
	t_token	*current;

	(void)ex;
	if (env == NULL && *env == NULL)
		return (0);
	current = node->data;
	if (current->next == NULL)
		return (export_no_arg(env));
	else
	{
		current = current->next;
		if (argument_checker(current->str) != 0)
		{
			ft_putendl_fd(" not a valid identifier", 2);
			return (1);
		}
		if (current->type == TK_Assign || ft_strchr(current->str, '='))
			return (export_assign(current->str, env));
		else if (current->type == TK_String)
			return (export_string(current->str, env));
	}
	return (0);
}
