/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_helper_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:38 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 22:40:54 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// ENVP: free individual node
void	ft_lstdelone_env(t_env *lst)
{
	if (lst != NULL)
	{
		free(lst->key);
		free(lst->value);
		free(lst);
	}
}

// ENVP: clear and free the linked list
void	ft_lstclear_env(t_env **lst)
{
	t_env	*temp;

	if (*lst != NULL && lst != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			ft_lstdelone_env(*lst);
			*lst = temp;
		}
	}
}

// ENVP: add node to the back
void	ft_lstadd_back_env(t_env **lst, t_env *new_env)
{
	t_env	*temp;

	if (*lst == NULL)
		*lst = new_env;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_env;
	}
}

// ENVP: extract value
char	*ft_substring_value(char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while (*s != '=')
		s++;
	s++;
	while (s[i] != '\0')
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// ENVP: extract key
char	*ft_substring_key(char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while (s[i] != '=')
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '=')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
