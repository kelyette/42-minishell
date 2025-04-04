/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/04 17:45:54 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "minishell.h"

typedef enum	e_token_t
{
	TKNull,
	TKString,
	TKIn,
	TKOut,
	TKCtrl,
	TKPipe,
	TKUSD,
}	e_token_t;

typedef struct s_token
{
	e_token_t		type;
	char			*str;
	struct s_token	*next;
}	t_token;

char	*ft_substr(char const *s, unsigned int start, size_t len);
// t_token	*ft_lstnew(t_token new_token);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);

t_token	*lexer(char *line);

#endif
