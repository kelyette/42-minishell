/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   No_copy_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:19 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 22:25:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// TOKEN: free individual node
void	ft_lstdelone_token(t_token *lst)
{
	if (lst != NULL)
	{
		free(lst->str);
		free(lst);
	}
}

// TOKEN: clear and free the linked list
void	ft_lstclear_token(t_token **lst)
{
	t_token	*temp;

	if (*lst != NULL && lst != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			ft_lstdelone_token(*lst);
			*lst = temp;
		}
	}
}

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
			builtin_echo(&node, &env);
		}
		else if (!ft_strncmp(node.data->str, "pwd", 4))
		{
			if (builtin_pwd(&env))
				return (1);
		}
		else if (!ft_strncmp(node.data->str, "env", 4))
		{
			builtin_env(&env);
		}
		else if (!ft_strncmp(node.data->str, "export", 7))
		{
			builtin_export(&node, &env);
		}
		else if (!ft_strncmp(node.data->str, "unset", 6))
		{
			builtin_unset(&node, &env);
		}
		else if (!ft_strncmp(node.data->str, "cd", 3))
		{
			builtin_cd(&node, &env);
		}
		else if (!ft_strncmp(node.data->str, "exit", 5))
		{
			builtin_exit(&node, &env);
		}
	}
	ft_lstclear_token(&head);
	ft_lstclear_env(&env);
	return (0);
}
