/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:22:49 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/26 10:22:29 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "envp.h"

t_bltnf	lookup_builtin(char *name)
{
	static const struct s_builtin	table[] = {
	{"echo", builtin_echo},
	{"pwd", builtin_pwd},
	{"env", builtin_env},
	{"export", builtin_export},
	{"cd", builtin_cd},
	{"exit", builtin_exit},
	{"unset", builtin_unset}};
	int								i;
	int								size;

	if (!name || !*name)
		return (NULL);
	size = sizeof(table) / sizeof(table[0]);
	i = 0;
	while (i < size)
	{
		if (!ft_strncmp(name, table[i].str, ft_strlen(table[i].str)))
			return (table[i].fn);
		i++;
	}
	return (NULL);
}
