/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/07 10:46:15 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*head;

	(void) ac;
	(void) av;
	(void) envp;
	while (1)
	{
		line = readline("Minishell> ");
		if (line != NULL && line[0] != '\0')
		{
			if (lexer(line, &head))
				return (perror("Error: "), 1);
			free(line);
			t_token	*temp;
			temp = head;
			while (temp != NULL)
			{
				printf("token: %s\n type: %d\n", temp->str, temp->type);
				temp = temp->next;
			}
			ft_lstclear(&head);
		}
	}
	return (0);
}
