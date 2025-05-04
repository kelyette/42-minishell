/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:48:40 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/04 16:57:21 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	set_get_code(int code, t_env **env)
{
	t_env	*temp;
	char	*tmp;
	
	temp = *env;
	while (temp != NULL)
	{
		if (!ft_strncmp(temp->key, "?", 2))
			break ;
		temp = temp->next;
	}
	if (code == -1)
		code = ft_atoi(temp->value);
	else
	{
		tmp = ft_itoa(code);
		if (tmp == NULL)
			return (perror("Error"), 1);
		free(temp->value);
		temp->value = tmp;
	}
	return (code);
}
