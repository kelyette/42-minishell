/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/22 17:42:59 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# define GROUP_MASK 0b11110000
# define GRP_SIMPLE 0
# define GRP_REDIR  16
# define GRP_PIPE   32
# define GRP_BIN    48

enum	e_token_t
{
	TK_Null, // 0
	TK_String = GRP_SIMPLE | 1, // 1
	TK_Assign = GRP_SIMPLE | 2, // 2
	TK_USD = GRP_SIMPLE | 3,// 3
	TK_Number = GRP_REDIR | 1, // 17
	TK_In = GRP_REDIR | 2,// 18
	TK_Out = GRP_REDIR | 3,// 19
	TK_HereDoc = GRP_REDIR | 4,// 20
	TK_Append = GRP_REDIR | 5,// 21
	TK_Pipe = GRP_PIPE | 1,// 33
	TK_And = GRP_BIN | 1,// 49
	TK_Or = GRP_BIN | 2,// 50
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

char	*ft_substring(char *s, int len);
int		ft_isalphabet(int c);
int		ft_isspace(char c);
int		ft_isnumber(int c);
int		ft_isprintable(int c);
void	ft_lstadd_back(t_token **lst, t_token *new_token);
void	ft_lstclear(t_token **lst);

int		lexer(char *line, t_token **head);
t_token	**case_single_char(t_token **head, char character);
t_token	**case_double_char(t_token **head, char character);
t_token	**case_printable(t_token **head, char *line, int *count);
void	case_string_helper2(t_token **token, char *line, int *count);

#endif
