/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:46:05 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/04 17:58:38 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_token	**case_USD(t_token **head, char )
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TKUSD;
	token->str = malloc(sizeof(char) * 2);
	if (token->str == NULL)
		return (free(token), NULL);
	token->str[0] = '$';
	token->str[1] = '\0';
	ft_lstadd_back(head, token);
	return (head);
}

// tokenizer, note: "" and '' not removed to 
// take care of $ in string later, treat with ft_strtrim
t_token	*lexer(char *line)
{
	t_token *head;
	int		i;

	i = 0;
	head = NULL;
	while (line[i] != '\0')
	{
		if (line[i] != '\"' && line[i] != '\'')
		{
			if (line[i] == '$')
			{
				if (case_USD(&head) == NULL)
					return (ft_lstclear(&head), NULL);
			}
			if (line[i] == '|' && line[i - 1] != '|' && line[i + 1] != '|')
			{
				if (case_pipe(&head) == NULL)
					return (ft_lstclear(&head), NULL);
			}
			i++;
		}
		else
		{
			printf("test\n");
			i++;
		}
		
	}
	// printf("token: %s\n", head->str);
	return (head);
}
