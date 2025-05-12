/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:46:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/12 22:52:08 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexer_helper(char *line, t_token **head, int *i, t_env **env)
{
	int		count;

	if ((line[*i] == '|' && line[*i + 1] != '|')
		|| (line[*i] == '<' && line[*i + 1] != '<')
		|| (line[*i] == '>' && line[*i + 1] != '>'))
	{
		if (case_single_char(head, line[*i]) == NULL)
			return (ft_lstclear_token(head), set_get_code(1, env));
	}
	else if ((line[*i] == '|' && line[*i + 1] == '|')
		|| (line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '&' && line[*i + 1] == '&'))
	{
		if (case_double_char(head, line[*i]) == NULL)
			return (ft_lstclear_token(head), set_get_code(1, env));
		(*i)++;
	}
	else if (ft_isprintable(line[*i]) && !ft_isspace(line[*i]))
	{
		if (case_printable(head, &line[*i], &count) == NULL)
			return (ft_lstclear_token(head), set_get_code(1, env));
		*i += count - 1;
	}
	return (set_get_code(0, env));
}

// tokenizer, 
// note: "" and '' not removed because of $ in string, treat with ft_strtrim
int	lexer(char *line, t_token **head, t_env **env)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '$' && !ft_isspace(line[i + 1]) && line[i + 1] != '\0'
			&& line[i + 1] != '<' && line[i + 1] != '>' && line[i + 1] != '|')
		{
			if (case_single_char(head, line[i]) == NULL)
				return (ft_lstclear_token(head), set_get_code(1, env));
		}
		else
		{
			if (lexer_helper(line, head, &i, env) == 1)
				return (set_get_code(1, env));
		}
		i++;
	}
	return (set_get_code(0, env));
}
