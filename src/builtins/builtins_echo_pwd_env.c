/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_pwd_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:53:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 16:42:12 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// case echo
int	builtin_echo(t_node *node, t_env **env)
{
	int	flag;

	(void)env;
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
	return (1);
}

// case env
int	builtin_env(t_node *node, t_env **env)
{
	t_env	*temp;

	(void)node;
	if (env == NULL && *env == NULL)
		return (0);
	temp = *env;
	while (temp != NULL)
	{
		if (temp->exported == true && temp->code == false)
		{
			printf("%s=%s\n", temp->key, temp->value);
		}
		temp = temp->next;
	}
	return (0);
}

// case pwd
int	builtin_pwd(t_node *node, t_env **env)
{
	char	*line;

	(void)node;
	(void)env;
	line = getcwd(NULL, 0);
	if (line == NULL)
		return (perror("Error"), 1);
	printf("%s\n", line);
	free(line);
	return (0);
}
