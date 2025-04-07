/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:46:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/07 12:00:03 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// tokenizer, 
// note: "" and '' not removed because of $ in string, treat with ft_strtrim
int	lexer(char *line, t_token **head)
{
	int		i;
	int		count;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue ;
		}
		if (line[i] == '$' && !ft_isspace(line[i + 1]))
		{
			if (case_single_char(head, line[i]) == NULL)
				return (ft_lstclear(head), 1);
		}
		else if ((line[i] == '|' && line[i + 1] != '|')
			|| (line[i] == '<' && line[i + 1] != '<')
			|| (line[i] == '>' && line[i + 1] != '>'))
		{
			if (case_single_char(head, line[i]) == NULL)
				return (ft_lstclear(head), 1);
		}
		else if ((line[i] == '|' && line[i + 1] == '|')
			|| (line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '&' && line[i + 1] == '&'))
		{
			if (case_double_char(head, line[i]) == NULL)
				return (ft_lstclear(head), 1);
			i++;
		}
		else if (ft_isprintable(line[i]) && !ft_isspace(line[i]))
		{
			if (case_printable(head, &line[i], &count) == NULL)
				return (ft_lstclear(head), 1);
			i += count - 1;
		}
		i++;
	}
	return (0);
}
