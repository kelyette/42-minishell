/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:39:54 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 16:57:27 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envp.h"

// handle cd path
int	case_cd_path(char *path, t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*line;

	pwd = get_env_key(env, "PWD");
	if (pwd == NULL)
		pwd = initiate_pwd_env(env);
	oldpwd = get_env_key(env, "OLDPWD");
	if (oldpwd == NULL)
		oldpwd = initiate_oldpwd_env(env);
	if (oldpwd == NULL || pwd == NULL)
		return (perror("Error"), 1);
	if (chdir(path) != 0)
		return (perror("Error"), 1);
	line = getcwd(NULL, 0);
	if (line == NULL)
		return (perror("Error"), 1);
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = line;
	return (0);
}

// handle cd -
int	case_cd_previous(t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	oldpwd = get_env_key(env, "OLDPWD");
	if (oldpwd == NULL)
		return (ft_putendl_fd("OLDPWD not set", 2), 1);
	pwd = get_env_key(env, "PWD");
	if (pwd != NULL)
		tmp = pwd->value;
	else
	{
		tmp = getcwd(NULL, 0);
		if (tmp == NULL)
			return (perror("Error"), 1);
	}
	if (chdir(oldpwd->value) != 0)
		return (perror("Error"), 1);
	if (pwd != NULL)
		pwd->value = oldpwd->value;
	else
		free(oldpwd->value);
	oldpwd->value = tmp;
	return (0);
}

int	case_cd_home(char *path, t_env **env)
{
	t_env	*home;
	char	*new_path;
	char	*temp;

	(void)new_path;
	home = get_env_key(env, "HOME");
	if (home == NULL)
		return (ft_putendl_fd("HOME not set", 2), 1);
	temp = ft_strdup(&path[1]);
	if (temp == NULL)
		return (perror("Error"), 1);
	new_path = ft_strjoin(home->value, temp);
	free(temp);
	if (new_path == NULL)
		return (perror ("Error"), 1);
	if (case_cd_path(new_path, env) != 0)
		return (free(new_path), 1);
	free(new_path);
	return (0);
}

// handle cd without argument
int	case_cd_no_arg(t_env **env)
{
	t_env	*home;

	home = get_env_key(env, "HOME");
	if (home == NULL)
		return (ft_putendl_fd("HOME not set", 2), 1);
	return (case_cd_path(home->value, env));
}

// case cd
int	builtin_cd(t_node *node, t_env **env, t_exec ex)
{
	t_token	*current;

	(void)ex;
	current = node->data;
	if (current->next == NULL)
		return (case_cd_no_arg(env));
	if (current->next->next != NULL)
		return (ft_putendl_fd(" too many arguments", 2), 1);
	current = current->next;
	if (!ft_strncmp(current->str, "~", 1))
		return (case_cd_home(current->str, env));
	if (!ft_strncmp(current->str, "-", 2))
		return (case_cd_previous(env));
	else
		return (case_cd_path(current->str, env));
	return (0);
}
