/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:53:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/08 05:52:32 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <string.h>

t_token	*expect_token(t_token *tkn, int type)
{
	if (!tkn->next)
		return (printf("error: unexpected end of line\n"), NULL);
	if (tkn->next->type != type)
		return (printf("error: invalid syntax near \"%s\"\n",
				tkn->next->str), NULL);
	return (tkn->next);
}

int	append_tkn_copy(t_token *base, t_token *next)
{
	while (base->next)
		base = base->next;
	base->next = malloc(sizeof(t_node));
	memcpy(base->next, next, sizeof(t_node)); // TODO forbidden func
	return (0);
}

int	token2argv(union u_data *dataptr)
{
	t_args	*args;
	t_token	*tkn;
	int		i;

	if (!dataptr->token)
		return (0);
	args = malloc(sizeof(t_args));
	tkn = dataptr->token->next;
	args->argc = 1;
	while (tkn && ++args->argc)
		tkn = tkn->next;
	args->argv = malloc(args->argc * sizeof(t_token *));
	tkn = dataptr->token;
	i = 0;
	while (tkn)
	{
		args->argv[i++] = tkn->str;
		tkn = tkn->next;
	}
	dataptr->args = args;
	return (0);
}
