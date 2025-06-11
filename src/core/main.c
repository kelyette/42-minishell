/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:37:47 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/11 11:41:27 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int	run_helper(t_token **head, t_env **env, char *line)
{
	char	*tmp;
	t_node	*tree;
	int		rval;

	tmp = dollar_handler(line, env);
	free(line);
	if (tmp == NULL)
		return (set_get_code(1, env));
	if (lexer(tmp, head, env))
		return (free(tmp), set_get_code(1, env));
	free(tmp);
	if (head != NULL && *head != NULL)
	{
		rval = parse(*head, &tree);
		if (rval != 0)
			set_get_code(rval, env);
		ft_lstclear_token(head);
		if (tree)
			executor((t_exec){&tree, env, 0}, tree);
		free_tree(&tree);
	}
	return (0);
}

int	empty_handler(char *line, t_env **env)
{
	int	i;

	i = 6;
	if (get_env_key(env, "EMPTY"))
		return (1);
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (set_get_code(0, env));
}

// main helper because of line count
int	run(t_token **head, t_env **env)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell> ");
		if (line == NULL)
			return (printf("exit\n"), set_get_code(-1, env));
		history_handler(line);
		if (line != NULL && line[0] != '\0')
		{
			if (!ft_strncmp(line, "$EMPTY", 6))
			{
				if (empty_handler(line, env) == 0)
				{
					free(line);
					continue ;
				}
			}
			if (run_helper(head, env, line) == 1)
				return (1);
			continue ;
		}
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token	*head;
	t_env	*env;
	int		ec;

	(void) ac;
	(void) av;
	head = NULL;
	env = NULL;
	if (transform_env(&env, envp))
		return (1);
	if (signal_handler())
		return (set_get_code(1, &env));
	ec = run(&head, &env);
	return (rl_clear_history(), ft_lstclear_env(&env), ec);
}
