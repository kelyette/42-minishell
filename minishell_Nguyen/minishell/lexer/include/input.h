/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/10 19:46:32 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "minishell.h"
# define GROUP_MASK 0b11110000
# define GROUP1     16
# define GROUP2     32
# define GROUP3     48

enum    e_token_t
{
    TK_Null, // 0
    TK_String, //= 1,// 1
    TK_Assign, //= 2,// 2
    TK_USD, //= 3,// 3
    TK_In, //= GROUP1 | 1,// 17
    TK_Out, //= GROUP1 | 2,// 18
    TK_HereDoc, //= GROUP1 | 3,// 19
    TK_Append, //= GROUP1 | 4,// 20
    TK_Pipe, //= GROUP2 | 1,// 33
    TK_And, //= GROUP3 | 1,// 49
    TK_Or, //= GROUP3 | 2,// 50
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
void	ft_lstadd_back(t_token **lst, t_token *new_token);
void	ft_lstclear(t_token **lst);

int		lexer(char *line, t_token **head);
t_token	**case_single_char(t_token **head, char character);
t_token	**case_double_char(t_token **head, char character);
t_token	**case_printable(t_token **head, char *line, int *count);
void	case_string_helper2(t_token **token, char *line, int *count);

#endif