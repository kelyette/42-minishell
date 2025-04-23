/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:46:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/23 19:06:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	lexer_helper(char *line, t_token **head, int *i)
{
	int		count;

	if ((line[*i] == '|' && line[*i + 1] != '|')
		|| (line[*i] == '<' && line[*i + 1] != '<')
		|| (line[*i] == '>' && line[*i + 1] != '>'))
	{
		if (case_single_char(head, line[*i]) == NULL)
			return (ft_lstclear_token(head), 1);
	}
	else if ((line[*i] == '|' && line[*i + 1] == '|')
		|| (line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '&' && line[*i + 1] == '&'))
	{
		if (case_double_char(head, line[*i]) == NULL)
			return (ft_lstclear_token(head), 1);
		(*i)++;
	}
	else if (ft_isprintable(line[*i]) && !ft_isspace(line[*i]))
	{
		if (case_printable(head, &line[*i], &count) == NULL)
			return (ft_lstclear_token(head), 1);
		*i += count - 1;
	}
	return (0);
}

// tokenizer, 
// note: "" and '' not removed because of $ in string, treat with ft_strtrim
int	lexer(char *line, t_token **head)
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
				return (ft_lstclear_token(head), 1);
		}
		else
		{
			if (lexer_helper(line, head, &i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
