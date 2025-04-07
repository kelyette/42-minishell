/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_case_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:31:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/07 10:34:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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

// handle unquoted string, and assignment
// FOR ASSIGNMENT: the assignment can only happen at the start of the command,
// or with export. To manage during ast or execution.
t_token	*case_string(t_token *token, char *line, int *count)
{
	int	flag;

	flag = 0;
	if (ft_isalphabet(line[0]) || line[0] == '_')
	{
		while (line[*count] != ' ' && line[*count] != '\0')
		{
			if (line[*count] == '=' && line[*count + 1] != ' ')
				flag = 1;
			(*count)++;
		}
	}
	else
	{
		while (line[*count] != ' ' && line[*count] != '\0')
			(*count)++;
	}
	token->type = TK_String;
	if (flag == 1)
		token->type = TK_Assign;
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
