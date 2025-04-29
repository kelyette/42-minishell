/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:19 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/29 12:59:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// test, to be delete, leak since no free
t_token	*create_token(t_token *head, char *av)
{
	t_token	*token;
	t_token	*temp;

	temp = head;
	token = malloc(sizeof(t_token));
	token->type = 1;
	token->str = ft_strdup(av);
	if (token->str[0] == 'U')
		token->type = TK_Assign;
	token->next = NULL;
	if (head == NULL)
		head = token;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = token;
	}
	return (head);
}

// test, to be delete, leak since no free
int	main(int ac, char **av, char **envp)
{
	t_node	node;
	t_token	*head;
	t_env	*env;
	int		i;

	if (ac > 1)
	{
		i = 1;
		head = NULL;
		env = NULL;
		while (i < ac)
		{
			head = create_token(head, av[i]);
			i++;
		}
		node.type = 1;
		node.lnode = NULL;
		node.rnode = NULL;
		node.data = head;
		transform_env(&env, envp);
		if (!ft_strncmp(node.data->str, "echo", 5))
		{
			if (builtin_echo(&node))
				return (1);
		}
		else if (!ft_strncmp(node.data->str, "pwd", 4))
		{
			if (builtin_pwd())
				return (1);
		}
		else if (!ft_strncmp(node.data->str, "env", 4))
		{
			if (builtin_env(&env))
				return (1);
		}
		else if (!ft_strncmp(node.data->str, "export", 7))
		{
			if (builtin_export(&node, &env))
				return (1);
		}
	}
	return (0);
}
