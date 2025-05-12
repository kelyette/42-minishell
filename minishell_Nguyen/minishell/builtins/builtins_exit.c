/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:38:25 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 22:10:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	clean_exit(int code, t_env **env) //Update to cleanup ast tree and such
{
	ft_lstclear_env(env);
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	exit(code);
}

int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isnumber(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exit_with_number(char *number, t_env **env)
{
	unsigned int	code;

	code = (unsigned int)ft_atoi(number);
	if (code > 256)
		code = code % 256;
	clean_exit(code, env); //Update to cleanup ast tree and such
}

void	exit_no_arg(t_env **env)
{
	int	code;

	code = set_get_code(-1, env);
	clean_exit(code, env); //Update to cleanup ast tree and such
}

int	builtin_exit(t_node *node, t_env **env) //need to pass in ast tree to clean up
{
	if (env == NULL && *env == NULL)
		return (0);
	if (node->data->next == NULL)
		return (exit_no_arg(env), 0);
	node->data = node->data->next;
	if (check_number(node->data->str))
		return (printf("Numeric argument required\n"), clean_exit(255, env), 0);
	if (node->data->next != NULL)
		return (printf("Too many argument\n"), set_get_code(1, env), 1);
	return (exit_with_number(node->data->str, env), 0);
}
