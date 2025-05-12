/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_pwd_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:53:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 22:24:28 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// case echo
int	builtin_echo(t_node *node, t_env **env)
{
	int	flag;

	flag = 0;
	node->data = node->data->next;
	if (!ft_strncmp(node->data->str, "-n", 3))
	{
		flag = 1;
		node->data = node->data->next;
	}
	while (node->data != NULL)
	{
		printf("%s", node->data->str);
		if (node->data->next != NULL)
			printf(" ");
		node->data = node->data->next;
	}
	if (flag == 0)
		printf("\n");
	return (set_get_code(0, env));
}

// case env
int	builtin_env(t_env **env)
{
	t_env	*temp;

	if (env == NULL && *env == NULL)
		return (set_get_code(0, env));
	temp = *env;
	while (temp != NULL)
	{
		if (temp->exported == true && temp->code == false)
		{
			printf("%s=%s\n", temp->key, temp->value);
		}
		temp = temp->next;
	}
	return (set_get_code(0, env));
}

// case pwd
int	builtin_pwd(t_env **env)
{
	char	*line;

	line = getcwd(NULL, 0);
	if (line == NULL)
		return (perror("Error"), set_get_code(1, env));
	printf("%s\n", line);
	free(line);
	return (set_get_code(0, env));
}
