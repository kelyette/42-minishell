/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:18:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/06/10 21:24:33 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>
#include "libft.h"

int	save_some_more_line(char **temp, char **pathptr)
{
	struct stat	st;

	if (stat(*temp, &st) == 0 && S_ISDIR(st.st_mode))
		return (ft_putstr_fd(*temp, 2), free(*temp),
			ft_putendl_fd(": Is a directory", 2), 126);
	if (access(*temp, X_OK) == 0)
	{
		*pathptr = *temp;
		return (-1);
	}
	else
		return (free(*temp), perror("minishell"), 126);
}

int	cmd_path_helper(char *line, char *copy, char **pathptr)
{
	char	*temp;

	while (copy != NULL)
	{
		temp = ft_strjoin(copy, line);
		if (temp == NULL)
			return (perror("Error"), 1);
		if (access(temp, F_OK) == 0)
			return (save_some_more_line(&temp, pathptr));
		free(temp);
		temp = ft_strrchr(copy, '/');
		if (temp != NULL)
			*temp = '\0';
		else
		{
			free(copy);
			break ;
		}
	}
	return (0);
}

char	*save_some_line(char *cmd, char **line, int *flag)
{
	char	*temp;
	char	*temp1;

	*flag = 1;
	if (cmd != NULL && cmd[0] == '.')
	{
		temp1 = &cmd[1];
		temp = getcwd(NULL, 0);
		if (temp == NULL)
			return (perror("Error"), NULL);
		*line = ft_strjoin(temp, temp1);
		if (*line == NULL)
			return (perror("Error"), free(temp), NULL);
		return (free(temp), *line);
	}
	else if ((cmd != NULL && cmd[0] != '/' && ft_strchr(cmd, '/') == NULL))
	{
		*line = ft_strjoin("/", cmd);
		*flag = 0;
	}
	else
		*line = ft_strdup(cmd);
	if (*line == NULL)
		return (NULL);
	return (*line);
}

int	cmd_path(char **paths, char **pathptr, char *cmd, int *count)
{
	char	*line;
	char	*copy;
	int		temp;
	int		flag;

	line = save_some_line(cmd, &line, &flag);
	if (line == NULL)
		return (1);
	while (paths[*count] != NULL)
	{
		copy = ft_strdup(paths[(*count)++]);
		if (copy == NULL)
			return (perror("Error"), 1);
		temp = cmd_path_helper(line, copy, pathptr);
		if (temp == -1)
			return (free(line), free(copy), 0);
		else if (temp == 126 || temp == 1)
			return (free(line), free(copy), temp);
	}
	if (flag == 0)
		return (free(line), ft_putstr_fd(cmd, 2),
			ft_putendl_fd(": command not found", 2), 127);
	else
		return (free(line), ft_putstr_fd(cmd, 2),
			ft_putendl_fd(": No such file or directory", 2), 127);
}

int	search_bin_path(char **pathptr, t_env **env, char *name)
{
	t_env		*env_path;
	char		**paths;
	int			code;
	int			count;

	if (!name)
		return (0);
	env_path = get_env_key(env, "PATH");
	if (!env_path || !env_path->value || !*env_path->value)
	{
		if (name[0] != '/')
			*pathptr = ft_strjoin("/", name);
		else
			*pathptr = ft_strdup(name);
		return (0);
	}
	paths = ft_split(env_path->value, ':');
	if (!paths)
		return (1);
	count = 0;
	code = cmd_path(paths, pathptr, name, &count);
	if (code != 0)
		return (ft_free_split(paths), code);
	ft_free_split(paths);
	return (MS_OK);
}
