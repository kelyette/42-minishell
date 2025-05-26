/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:18:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/26 15:12:31 by kcsajka          ###   ########.fr       */
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
	if (!path)
		return (perror("minishell"), NULL);
	ft_memcpy(path, dir, dsize);
	path[dsize] = '/';
	ft_memcpy(path + dsize + 1, name, nsize);
	path[dsize + nsize + 1] = 0;
	return (path);
}

int	search_bin_path(char **pathptr, t_env **env, char *name)
{
	struct stat	st;
	t_env		*env_path;
	char		**paths;
	char		*tmp;
	int			i;

	env_path = get_env_key(env, "PATH");
	if (!name || !env_path || !env_path->value || !*env_path->value)
		return (0);
	paths = ft_split(env_path->value, ':');
	if (!paths)
		return (1);
	i = -1;
	while (paths[++i])
	{
		tmp = concat_path(paths[i], name);
		if (!tmp)
			return (1);
		if (!stat(tmp, &st) && S_ISREG(st.st_mode))
			return (ft_free_split(paths), (*pathptr = tmp), 0);
		free(tmp);
	}
	ft_free_split(paths);
	return (0);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir);
		redir = tmp;
	}
}
