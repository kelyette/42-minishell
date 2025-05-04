/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:35:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/04 16:57:19 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// to clarify on utility
int	g_signal;

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
			return (printf("exit\n"), rl_clear_history(), 0);
		history_handler(line);
		if (line != NULL && line[0] != '\0')
		{
			tmp = dollar_handler(line, env);
			free(line);
			if (tmp == NULL)
				return (1);
			printf("%s\n", tmp);//delete
			if (lexer(tmp, head))
				return (free(tmp), 1);
			ast_builder(head, env);//replace
			ft_lstclear_token(head);
		}
		free(tmp);
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
		return (rl_clear_history(), ft_lstclear_env(&env), 1);
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