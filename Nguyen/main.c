/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/04 17:50:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell > ");
		if (line != NULL && line[0] != '\0')
		{
			if (lexer(line) == NULL)
				return (printf("malloc fail"), 1);
			free(line);
		}
	}
	return (0);
}
