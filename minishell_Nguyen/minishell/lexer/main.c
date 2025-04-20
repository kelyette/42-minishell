/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/18 21:33:46 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "shellsignal.h"

// to clarify on utility
volatile sig_atomic_t	g_signal;

// change signal type
void	signal_change(int signal_attribute)
{
	g_signal = signal_attribute;
	if (g_signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 0;
	}
	else if (g_signal == SIGQUIT)
	{
		printf("^\\Quit (Core dumped)\n");
		rl_clear_history();
		exit (0);
	}
}

int	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_change;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) != 0)
		return (perror("Error"), 1);
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		return (perror("Error"), 1);
	return (0);
}

// to replace with ast
void	ast_builder(t_token *head, char **envp)
{
	t_token	*temp;

	(void) envp;
	temp = head;
	while (temp != NULL)
	{
		printf("token: %s \\ type: %d\n", temp->str, temp->type);
		temp = temp->next;
	}
}

// handle history
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
	char				*line;
	t_token				*head;

	(void) ac;
	(void) av;
	g_signal = 0;
	head = NULL;
	if (signal_handler())
		return (1);
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
			ast_builder(head, envp);
			ft_lstclear(&head);
		}
		free(line);
	}
	return (rl_clear_history(), 0);
}
