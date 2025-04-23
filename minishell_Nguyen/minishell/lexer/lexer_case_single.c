/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_case_single.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:14:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/23 18:15:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	case_output(t_token *token)
{
	token->type = TK_Out;
	token->str[0] = '>';
	token->str[1] = '\0';
	token->next = NULL;
}

void	case_input(t_token *token)
{
	token->type = TK_In;
	token->str[0] = '<';
	token->str[1] = '\0';
	token->next = NULL;
}

void	case_pipe(t_token *token)
{
	token->type = TK_Pipe;
	token->str[0] = '|';
	token->str[1] = '\0';
	token->next = NULL;
}

void	case_usd(t_token *token)
{
	token->type = TK_USD;
	token->str[0] = '$';
	token->str[1] = '\0';
	token->next = NULL;
}

// Handle $ , | , > , <
t_token	**case_single_char(t_token **head, char character)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (perror("Error"), NULL);
	token->str = malloc(sizeof(char) * 2);
	if (token->str == NULL)
		return (perror("Error"), free(token), NULL);
	if (character == '$')
		case_usd(token);
	else if (character == '|')
		case_pipe(token);
	else if (character == '<')
		case_input(token);
	else if (character == '>')
		case_output(token);
	ft_lstadd_back_token(head, token);
	return (head);
}
