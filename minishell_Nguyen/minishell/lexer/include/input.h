/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/23 16:01:44 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "minishell.h"
# define GROUP_MASK 0b11110000
# define GROUP1     16
# define GROUP2     32
# define GROUP3     48

extern sig_atomic_t	g_signal;

enum	e_token_t
{
	TK_Null,
	TK_String,
	TK_Assign,
	TK_USD,
	TK_In,
	TK_Out,
	TK_HereDoc,
	TK_Append,
	TK_Pipe,
	TK_And,
	TK_Or,
	TK_Number,
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
void	ft_lstadd_back_token(t_token **lst, t_token *new_token);
void	ft_lstclear_token(t_token **lst);

int		lexer(char *line, t_token **head);
t_token	**case_single_char(t_token **head, char character);
t_token	**case_double_char(t_token **head, char character);
t_token	**case_printable(t_token **head, char *line, int *count);
void	case_string_helper2(t_token **token, char *line, int *count);

int		signal_handler(void);

#endif