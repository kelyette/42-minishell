/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:46:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/03 11:29:15 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	skip_and_copy(char *src, char *dst, int *i, int *j, char quote)
{
	(*i)++;
	while (src[*i] && src[*i] != quote)
		dst[(*j)++] = src[(*i)++];
	if (src[*i] == quote)
		(*i)++;
}

char	*trim_quotes(char *raw_line)
{
	char	*clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean = malloc(ft_strlen(raw_line) + 1);
	if (!clean)
		return (perror("Error"), NULL);
	while (raw_line[i])
	{
		if (raw_line[i] == '\'' || raw_line[i] == '\"')
			skip_and_copy(raw_line, clean, &i, &j, raw_line[i]);
		else
			clean[j++] = raw_line[i++];
	}
	clean[j] = '\0';
	return (clean);
}

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
	else if (ft_isprint(line[*i]) && !ft_isspace(line[*i]))
	{
		if (case_printable(head, &line[*i], &count) == NULL)
			return (ft_lstclear_token(head), set_get_code(1, env));
		*i += count - 1;
	}
	return (set_get_code(0, env));
}

// tokenizer, 
// note: "" and '' not removed, treat with ft_strtrim
int	lexer(char *raw_line, t_token **head, t_env **env)
{
	int		i;
	char	*line;

	i = 0;
	line = trim_quotes(raw_line);
	printf("%s\n", line);
	(void)i;
	(void)line;
	(void)head;
	if (line == NULL)
		return (set_get_code(1, env));
	while (line[i] != '\0')
	{
		while (ft_isspace(line[i]))
			i++;
		if (!ft_isspace(line[i + 1]) && line[i + 1] != '\0'
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
