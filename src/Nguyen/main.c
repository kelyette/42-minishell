/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/04 14:56:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	lexer(char *line)
{
	
	return (0);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell > ");
		if (line != NULL && line[0] != '\0')
		{
			lexer(line);
			free(line);
		}
	}
	return (0);
}
