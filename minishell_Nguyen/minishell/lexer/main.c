/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/23 19:06:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "envp.h"

// to clarify on utility
sig_atomic_t	g_signal;

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

	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
			return (printf("exit\n"), rl_clear_history(), 0);
		history_handler(line);
		if (line != NULL && line[0] != '\0')
		{
			if (lexer(line, head))
				return (free(line), 1);
			ast_builder(head, env);
			ft_lstclear_token(head);
		}
		free(line);
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
	if (signal_handler())
		return (1);
	if (transform_env(&env, envp))
		return (1);
	if (run(&head, &env))
		return (1);
	return (rl_clear_history(), ft_lstclear_env(&env), 0);
}

// // loop to show ARRAY to LIST env
// while (env != NULL)
// {
// 	printf("%s", env->key);
// 	printf("=");
// 	printf("%s", env->value);
// 	printf("\n");
// 	env = env->next;
// }

// // loop to show LIST to ARRAY envp
// char **test;
// test = env_to_envp(&env);
// for (int i=0; test[i]; i++)
// {
// 	printf("%s\n", test[i]);
// }
// free_envp(test);