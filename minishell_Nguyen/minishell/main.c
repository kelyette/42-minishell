/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/07 12:25:43 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	history_handler(char *line)
{
	if (line != NULL && line[0] != '\0')
	{
		add_history(line);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*head;

	(void) ac;
	(void) av;
	(void) envp;
	head = NULL;
	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
			return (printf("exit\n"), rl_clear_history(), 0);
		history_handler(line);
		if (line != NULL && line[0] != '\0')
		{
			if (lexer(line, &head))
				return (free(line), perror("Error: "), 1);
			t_token	*temp;
			temp = head;
			while (temp != NULL)
			{
				printf("token: %s\n type: %d\n", temp->str, temp->type);
				temp = temp->next;
			}
			ft_lstclear(&head);
		}
		free(line);
	}
	return (rl_clear_history(), 0);
}
