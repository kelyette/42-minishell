/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   No_copy_envp_helper_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:26:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 16:28:20 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	initiate_base_env_helper_helper(t_env **env)
{
	t_env	*exit_code;

	exit_code = malloc(sizeof(t_env));
	if (exit_code == NULL)
		return (perror("Error"), ft_lstclear_env(env), 1);
	exit_code->key = ft_strdup("?");
	if (exit_code->key == NULL)
		return (1);
	exit_code->value = ft_strdup("0");
	if (exit_code->value == NULL)
		return (1);
	exit_code->exported = false;
	exit_code->only_key = false;
	exit_code->code = true;
	exit_code->printed = false;
	exit_code->next = NULL;
	(*env)->next->next = exit_code;
	return (0);
}

int	initiate_base_env_helper(t_env **env)
{
	t_env	*shlvl;

	shlvl = malloc(sizeof(t_env));
	if (shlvl == NULL)
		return (perror("Error"), ft_lstclear_env(env), 1);
	shlvl->key = ft_strdup("SHLVL");
	if (shlvl->key == NULL)
		return (1);
	shlvl->value = ft_strdup("1");
	if (shlvl->value == NULL)
		return (1);
	shlvl->exported = true;
	shlvl->only_key = false;
	shlvl->code = false;
	shlvl->printed = false;
	shlvl->next = NULL;
	(*env)->next = shlvl;
	return (initiate_base_env_helper_helper(env));
}

// in case of NULL envp,
// initiate 3 environnement variables PWD, SHLVL and exit code.
int	initiate_base_env(t_env **env)
{
	*env = malloc(sizeof(t_env));
	if (*env == NULL)
		return (perror("Error"), 1);
	(*env)->key = ft_strdup("PWD");
	if ((*env)->key == NULL)
		return (1);
	(*env)->value = getcwd(NULL, 0);
	if ((*env)->value == NULL)
		return (perror("Error"), 1);
	(*env)->exported = true;
	(*env)->only_key = false;
	(*env)->code = false;
	(*env)->printed = false;
	(*env)->next = NULL;
	return (initiate_base_env_helper(env));
}
