/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:35:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 22:54:04 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// to replace with ast
void	ast_builder(t_token **head, t_env **env)
{
	t_token	*temp;

	(void) env;
	temp = *head;
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

// main helper because of line count
int	run(t_token **head, t_env **env)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
			return (printf("exit\n"), set_get_code(0, env));
		history_handler(line);
		if (line != NULL && line[0] != '\0')
		{
			tmp = dollar_handler(line, env);
			free(line);
			if (tmp == NULL)
				return (set_get_code(1, env));
			printf("%s\n", tmp);//delete
			if (lexer(tmp, head, env))
				return (free(tmp), set_get_code(1, env));
			free(tmp);
			ast_builder(head, env);//replace
			ft_lstclear_token(head);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token	*head;
	t_env	*env;

	(void) ac;
	(void) av;
	head = NULL;
	env = NULL;
	if (transform_env(&env, envp))
		return (1);
	if (signal_handler())
		return (set_get_code(1, &env));
	if (run(&head, &env))
	{
		rl_clear_history();
		return (ft_lstclear_env(&env), 1);
	}
	rl_clear_history();
	return (ft_lstclear_env(&env), 0);
}
