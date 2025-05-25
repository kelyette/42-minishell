/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:22:49 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/24 23:23:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_bltnf	lookup_builtin(char *name)
{
	static const struct s_builtin	table[] = {
	{"echo", builtin_echo},
	{"pwd", builtin_pwd},
	{"env", builtin_env},
	{"export", builtin_export},
	{"cd", builtin_cd},
	{"exit", builtin_exit}}; // doesnt work
	size_t							size;

	if (!name || !*name)
		return (NULL);
	size = sizeof(table) / sizeof(table[0]);
	while (--size)
		if (!ft_strncmp(name, table[size].str, ft_strlen(table[size].str)))
			return (table[size].fn);
	return (NULL);
}
