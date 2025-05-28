/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/28 16:20:46 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "envp.h"

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
	t_node	*tree;

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
			if (lexer(tmp, head, env))
				return (free(tmp), set_get_code(1, env));
			free(tmp);
			if (parse(*head, &tree))
				return (ft_lstclear_token(head), set_get_code(1, env));
			ft_lstclear_token(head);
			//if (tree)
			//	print_tree(tree);
			if (tree)
				set_get_code(executor(tree, env), env);
			free_tree(&tree);
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
		return (rl_clear_history(), ft_lstclear_env(&env), 1);
	return (rl_clear_history(), ft_lstclear_env(&env), 0);
}
