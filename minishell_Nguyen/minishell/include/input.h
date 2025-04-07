/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/07 10:46:29 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "minishell.h"

enum	e_token_t
{
	TK_Null,// 0
	TK_String,// 1
	TK_Assign,// 2
	TK_In,// 3
	TK_Out,// 4
	TK_Pipe,// 5
	TK_USD,// 6
	TK_Heredoc,// 7
	TK_Append,// 8
	TK_And,// 9
	TK_Or,// 10
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

#endif