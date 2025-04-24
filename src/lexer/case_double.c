/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_case_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:15:44 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/23 21:02:52 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	case_append(t_token *token)
{
	token->type = TK_Append;
	token->str[0] = '>';
	token->str[1] = '>';
	token->str[2] = '\0';
	token->next = NULL;
}

void	case_heredoc(t_token *token)
{
	token->type = TK_HereDoc;
	token->str[0] = '<';
	token->str[1] = '<';
	token->str[2] = '\0';
	token->next = NULL;
}

void	case_or(t_token *token)
{
	token->type = TK_Or;
	token->str[0] = '|';
	token->str[1] = '|';
	token->str[2] = '\0';
	token->next = NULL;
}

void	case_and(t_token *token)
{
	token->type = TK_And;
	token->str[0] = '&';
	token->str[1] = '&';
	token->str[2] = '\0';
	token->next = NULL;
}

// Handle || , && , >> , <<
t_token	**case_double_char(t_token **head, char character)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (perror("Error"), NULL);
	token->str = malloc(sizeof(char) * 3);
	if (token->str == NULL)
		return (perror("Error"), free(token), NULL);
	if (character == '&')
		case_and(token);
	else if (character == '|')
		case_or(token);
	else if (character == '<')
		case_heredoc(token);
	else if (character == '>')
		case_append(token);
	ft_lstadd_back_token(head, token);
	return (head);
}
