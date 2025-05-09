/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:39:54 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/03 15:27:10 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
// handle cd path
int	case_cd_path(char *path, t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*line;

	if (chdir(path) != 0)
		return (perror("Error"), 1);
	line = getcwd(NULL, 0);
	if (line == NULL)
		return (perror("Error"), 1);
	oldpwd = find_oldpwd(env);
	pwd = find_pwd(env);
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = line;
	builtin_env(env);
	return (0);
}

// handle cd -
int	case_cd_previous(t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	oldpwd = find_oldpwd(env);
	if (oldpwd == NULL)
		return (printf("bash: cd: OLDPWD not set\n"), 1);
	pwd = find_pwd(env);
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
	home = find_home(env);
	if (home == NULL)
		return (printf("bash: cd: HOME not set\n"), 1);
	temp = ft_strdup(&path[1]);
	if (temp == NULL)
		return (1);
	new_path = ft_strjoin(home->value, temp);
	free(temp);
	if (new_path == NULL)
		return (1);
	if (case_cd_path(new_path, env) != 0)
		return (1);
	free(new_path);
	return (0);
}

// handle cd without argument
int	case_cd_no_arg(t_env **env)
{
	t_env	*home;

	home = find_home(env);
	if (home == NULL)
		return (printf("bash: cd: HOME not set\n"), 1);
	return (case_cd_path(home->value, env));
}

// case cd
int	builtin_cd(t_node *node, t_env **env)
{
	if (node->data->next == NULL)
		return (case_cd_no_arg(env));
	if (node->data->next->next != NULL)
		return (printf("bash: cd: too many arguments\n"), 1);
	node->data = node->data->next;
	if (!ft_strncmp(node->data->str, "~", 1))
		return (case_cd_home(node->data->str, env));
	if (!ft_strncmp(node->data->str, "-", 2))
		return (case_cd_previous(env));
	else
		return (case_cd_path(node->data->str, env));
	return (0);
}
