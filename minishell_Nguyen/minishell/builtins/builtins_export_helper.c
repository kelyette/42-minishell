/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:57:17 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/30 17:00:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_compare(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	if (i > j)
		return (i);
	else
		return (j);
}

t_env	*min_start(t_env **env, t_env *min)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		if (temp->code == false && temp->printed == false)
		{
			min = temp;
			return (min);
		}
		temp = temp->next;
	}
	return (min);
}

t_env	*get_variable_helper(t_env **env, t_env *min)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		if (temp->code == true || temp->printed == true)
		{
			temp = temp->next;
			continue ;
		}
		if (temp->code == false && temp->printed == false
			&& ft_strncmp(temp->key, min->key,
				ft_compare(temp->key, min->key)) < 0)
			min = temp;
		temp = temp->next;
	}
	return (min);
}

// get the variable to print by compare a key with all other keys,
// set the flag then do the same with the rest, return node to print
t_env	*get_variable(t_env **env)
{
	t_env	*min;
	t_env	*temp;

	min = NULL;
	min = min_start(env, min);
	min = get_variable_helper(env, min);
	if (min == NULL)
	{
		temp = *env;
		while (temp != NULL)
		{
			temp->printed = false;
			temp = temp->next;
		}
		return (NULL);
	}
	else
	{
		min->printed = true;
		return (min);
	}
}

// case export no argument
// the difficulty was to sort the env
int	export_no_arg(t_env **env)
{
	t_env	*temp;

	if (env == NULL || *env == NULL)
		return (0);
	while (1)
	{
		temp = get_variable(env);
		if (temp == NULL)
			return (0);
		else
		{
			if (temp->only_key == false)
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("declare -x %s\n", temp->key);
		}
	}
	return (0);
}
