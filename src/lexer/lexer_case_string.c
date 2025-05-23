/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_case_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:31:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 14:48:32 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*case_singlequote(t_token *token, char *line, int *cnt)
{
	char	*temp;

	(*cnt)++;
	while (line[*cnt] != '\'' && line[*cnt] != '\0')
		(*cnt)++;
	(*cnt)++;
	token->type = TK_String;
	temp = ft_substr(line, 0, *cnt);
	if (temp == NULL)
		return (NULL);
	token->str = ft_strtrim(temp, "\'");
	free(temp);
	if (token->str == NULL)
		return (perror("Error"), NULL);
	token->next = NULL;
	return (token);
}

t_token	*case_doublequote(t_token *token, char *line, int *cnt)
{
	char	*temp;

	(*cnt)++;
	while (line[*cnt] != '\"' && line[*cnt] != '\0')
		(*cnt)++;
	(*cnt)++;
	token->type = TK_String;
	temp = ft_substr(line, 0, *cnt);
	if (temp == NULL)
		return (NULL);
	token->str = ft_strtrim(temp, "\"");
	free(temp);
	if (token->str == NULL)
		return (perror("Error"), NULL);
	token->next = NULL;
	return (token);
}

void	case_string_helper1(t_token **token, char *line, int *cnt)
{
	while (ft_isdigit(line[*cnt]))
	{
		if (ft_isspace(line[*cnt + 1]) && !ft_isdigit(line[*cnt + 1]))
		{
			*cnt = 0;
			break ;
		}
		else if ((line[*cnt + 1] == '<' && line[*cnt + 2] != '<')
			|| (line[*cnt + 1] == '>' && line[*cnt + 2] != '>')
			|| (line[*cnt + 1] == '<' && line[*cnt + 2] == '<')
			|| (line[*cnt + 1] == '>' && line[*cnt + 2] == '>'))
		{
			(*token)->type = TK_Number;
			(*cnt)++;
			break ;
		}
		(*cnt)++;
	}
}

// handle unquoted string, and assignment
// FOR ASSIGNMENT: the assignment can only happen at the start of the command,
// or with export. To manage during ast or execution.
t_token	*case_string(t_token *token, char *line, int *cnt)
{
	token->type = TK_String;
	case_string_helper1(&token, line, cnt);
	if ((ft_isalpha(line[0]) || line[0] == '_') && token->type == TK_String)
	{
		while (line[*cnt] != ' ' && line[*cnt] != '\0'
			&& line[*cnt] != '<' && line[*cnt] != '>'
			&& line[*cnt] != '|' && line[*cnt] != '\"' && line[*cnt] != '\'')
		{
			if (line[*cnt] == '=')
				token->type = TK_Assign;
			(*cnt)++;
		}
	}
	else if (ft_isprint(line[0]) && token->type == TK_String)
	{
		while (line[*cnt] != ' ' && line[*cnt] != '\0'
			&& line[*cnt] != '<' && line[*cnt] != '>' && line[*cnt] != '|')
			(*cnt)++;
	}
	token->str = ft_substr(line, 0, *cnt);
	if (token->str == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

// handle String, with case double quote, single quote and no quote
t_token	**case_printable(t_token **head, char *line, int *cnt)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (perror("Error"), NULL);
	*cnt = 0;
	if (line[*cnt] == '\"')
	{
		if (case_doublequote(token, line, cnt) == NULL)
			return (free(token), NULL);
	}
	else if (line[*cnt] == '\'')
	{
		if (case_singlequote(token, line, cnt) == NULL)
			return (free(token), NULL);
	}
	else
	{
		if (case_string(token, line, cnt) == NULL)
			return (free(token), NULL);
	}
	ft_lstadd_back_token(head, token);
	return (head);
}
