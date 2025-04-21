/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_case_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:31:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/21 16:54:22 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*case_singlequote(t_token *token, char *line, int *count)
{
	(*count)++;
	while (line[*count] != '\'' && line[*count] != '\0')
		(*count)++;
	(*count)++;
	token->type = TK_String;
	token->str = ft_substring(line, *count);
	if (token->str == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

t_token	*case_doublequote(t_token *token, char *line, int *count)
{
	(*count)++;
	while (line[*count] != '\"' && line[*count] != '\0')
		(*count)++;
	(*count)++;
	token->type = TK_String;
	token->str = ft_substring(line, *count);
	if (token->str == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

void	case_string_helper1(t_token **token, char *line, int *count)
{
	while (ft_isnumber(line[*count]))
	{
		if (ft_isspace(line[*count + 1]) && !ft_isnumber(line[*count + 1]))
		{
			*count = 0;
			break ;
		}
		else if ((line[*count + 1] == '<' && line[*count + 2] != '<')
			|| (line[*count + 1] == '>' && line[*count + 2] != '>')
			|| (line[*count + 1] == '<' && line[*count + 2] == '<')
			|| (line[*count + 1] == '>' && line[*count + 2] == '>'))
		{
			(*token)->type = TK_Number;
			(*count)++;
			break ;
		}
		(*count)++;
	}
}

// handle unquoted string, and assignment
// FOR ASSIGNMENT: the assignment can only happen at the start of the command,
// or with export. To manage during ast or execution.
t_token	*case_string(t_token *token, char *line, int *count)
{
	token->type = TK_String;
	case_string_helper1(&token, line, count);
	if ((ft_isalphabet(line[0]) || line[0] == '_') && token->type == TK_String)
	{
		while (line[*count] != ' ' && line[*count] != '\0'
			&& line[*count] != '<' && line[*count] != '>'
			&& line[*count] != '|')
		{
			if (line[*count] == '=')
				token->type = TK_Assign;
			(*count)++;
		}
	}
	else if (ft_isprintable(line[0]) && token->type == TK_String)
	{
		while (line[*count] != ' ' && line[*count] != '\0'
			&& line[*count] != '<' && line[*count] != '>'
			&& line[*count] != '|')
			(*count)++;
	}
	token->str = ft_substring(line, *count);
	if (token->str == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

// handle String, with case double quote, single quote and no quote
t_token	**case_printable(t_token **head, char *line, int *count)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	*count = 0;
	if (line[*count] == '\"')
	{
		if (case_doublequote(token, line, count) == NULL)
			return (free(token), NULL);
	}
	else if (line[*count] == '\'')
	{
		if (case_singlequote(token, line, count) == NULL)
			return (free(token), NULL);
	}
	else
	{
		if (case_string(token, line, count) == NULL)
			return (free(token), NULL);
	}
	ft_lstadd_back(head, token);
	return (head);
}
