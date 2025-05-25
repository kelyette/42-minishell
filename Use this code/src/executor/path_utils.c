/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:18:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/24 23:19:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>
#include "libft.h"

char	*concat_path(const char *dir, const char *name)
{
	char	*path;
	size_t	dsize;
	size_t	nsize;

	dsize = ft_strlen(dir);
	nsize = ft_strlen(name);
	path = malloc(sizeof(char) * (dsize + nsize + 2));
	ft_memcpy(path, dir, dsize);
	path[dsize] = '/';
	ft_memcpy(path + dsize + 1, name, nsize);
	path[dsize + nsize + 1] = 0;
	return (path);
}

int	is_executable(const char *path)
{
	struct stat	st;

	if (stat(path, &st) || !S_ISREG(st.st_mode))
		return (0);
	if (access(path, X_OK))
		return (0);
	return (1);
}

char	*search_bin_path(t_env **env, char *name)
{
	t_env	*env_path;
	char	**paths;
	char	*tmp;
	int		i;

	if (!name || !*name)
		return (NULL);
	env_path = get_env_key(env, "PATH");
	if (!env_path || !env_path->value || !*env_path->value)
		return (NULL);
	paths = ft_split(env_path->value, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = concat_path(paths[i], name);
		if (is_executable(tmp))
			return (ft_free_split(paths), tmp);
		free(tmp);
	}
	ft_free_split(paths);
	return (NULL);
}
