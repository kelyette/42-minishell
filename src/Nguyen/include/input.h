/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/04 15:05:43 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "minishell.h"

enum	e_token_t
{
	TKNull,
	TKCmd,
	TKIn,
	TKOut,
	TKCtrl,
	TKPipe,
	TKUSD,
}	e_token_t;

typedef struct s_token
{
	e_token_t	type;
	char		*str;
}	t_token;

t_token	*tokenize(char *str);

#endif
