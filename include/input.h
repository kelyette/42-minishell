/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/02 19:19:04 by kcsajka          ###   ########.fr       */
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
};

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

t_token	*tokenize(char *str);

#endif
