/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:38:25 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/04 21:11:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	clean_exit(int code, t_env **env) //Update to cleanup ast tree and such
{
	ft_lstclear_env(env);
	rl_clear_history();
	if (isatty(STDIN_FILENO))
	{
		printf("exit\n");
	}
	exit(code);
}

int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
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
	t_token	*current;

	if (env == NULL && *env == NULL)
		return (0);
	current = node->data;
	if (current->next == NULL)
		return (exit_no_arg(env), 0);
	current = current->next;
	if (check_number(current->str))
		return (ft_putendl_fd(" numeric argument required", 2), clean_exit(2, env), 0);
	if (current->next != NULL)
		return (ft_putendl_fd(" too many arguments", 2), 1);
	return (exit_with_number(current->str, env), 0);
}
