/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   path_utils.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hoannguy <hoannguy@student.42lausanne.c	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/05 16:18:57 by kcsajka		   #+#	#+#			 */
/*   Updated: 2025/06/11 10:13:34 by hoannguy		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>
#include "libft.h"

int	save_line(char *temp, char **pathptr)
{
	struct stat	st;

	if (stat(temp, &st) == 0 && S_ISDIR(st.st_mode))
		return (ft_putstr_fd(temp, 2), free(temp),
			ft_putendl_fd(": Is a directory", 2), 126);
	if (access(temp, X_OK) == 0)
	{
		*pathptr = ft_strdup(temp);
		return (free(temp), 0);
	}
	else
		return (free(temp), perror("minishell"), 126);
	return (0);
}

int	case_normal(char **pathptr, t_env **env, char *name, char *tmp)
{
	t_env	*env_path;
	char	**path;
	char	*temp;
	int		i;

	env_path = get_env_key(env, "PATH");
	if (!env_path || !env_path->value || !*env_path->value)
		return (ft_putstr_fd(name, 2),
			ft_putendl_fd(": No such file or directory", 2), 127);
	path = ft_split(env_path->value, ':');
	if (!path)
		return (perror("Error"), 1);
	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], tmp);
		if (access(temp, F_OK) == 0)
			return (free(tmp), ft_free_split(path), save_line(temp, pathptr));
		else
			free(temp);
	}
	return (free(tmp), ft_free_split(path), ft_putstr_fd(name, 2),
		ft_putendl_fd(": command not found", 2), 127);
}

int	case_slash(char **pathptr, char *name)
{
	struct stat	st;

	if (stat(name, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (ft_putstr_fd(name, 2),
				ft_putendl_fd(": Is a directory", 2), 126);
		if (access(name, X_OK) == 0)
		{
			*pathptr = ft_strdup(name);
			if (*pathptr == NULL)
				return (perror("minishell"), 1);
			return (0);
		}
		else
			return (ft_putstr_fd(name, 2),
				ft_putendl_fd(": Permission denied", 2), 126);
	}
	else
		return (ft_putstr_fd(name, 2),
			ft_putendl_fd(": No such file or directory", 2), 127);
}

int	search_bin_path(char **pathptr, t_env **env, char *name)
{
	int		i;
	char	*temp;

	if (!name)
		return (0);
	i = -1;
	while (name[++i])
	{
		if (name[i] == '/')
			return (case_slash(pathptr, name));
	}
	temp = ft_strjoin("/", name);
	if (temp == NULL)
		return (perror("minishell"), 1);
	return (case_normal(pathptr, env, name, temp));
}
