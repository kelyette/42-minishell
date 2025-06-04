/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_case_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:31:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/04 12:35:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	case_quoted(char *line, int *i, int *assign)
{
	char	quote;
	int		start;

	quote = line[(*i)++];
	start = *i;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '=' && *assign == 0)
			*assign = 1;
		(*i)++;
	}
	return (start);
}

int	case_non_quoted(char *line, int *i, int *assign)
{
	int	start;

	start = *i;
	while (is_valid_char(line[*i]) && line[*i] != '\'' && line[*i] != '\"')
	{
		if (line[*i] == '=' && *assign == 0)
			*assign = 1;
		(*i)++;
	}
	return (start);
}

int	append_segment(char **result, char *line, int start, int end)
{
	char	*temp;
	char	*joined;

	temp = ft_substr(line, start, end - start);
	if (!temp)
		return (-1);
	joined = ft_strjoin_free(*result, temp);
	if (!joined)
	{
		free(temp);
		return (-1);
	}
	*result = joined;
	return (0);
}

t_token	*case_string_parse(t_token *token, char *line, int *i, char **result)
{
	int		start;
	int		assign;

	assign = 0;
	while (line[*i] && is_valid_char(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			start = case_quoted(line, i, &assign);
		else
			start = case_non_quoted(line, i, &assign);
		if (start == -1 || append_segment(result, line, start, *i) == -1)
			return (free(*result), perror("Error"), NULL);
		if (line[*i] == '\'' || line[*i] == '\"')
			(*i)++;
	}
	if (assign)
		token->type = TK_Assign;
	else
		token->type = TK_String;
	return (token);
}

t_token	*case_string(t_token *token, char *line, int *cnt)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (perror("Error"), NULL);
	token = case_string_parse(token, line, &i, &result);
	if (!token)
		return (NULL);
	*cnt = i;
	token->str = result;
	token->next = NULL;
	return (token);
}
