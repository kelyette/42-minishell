/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/05 17:56:54 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "envp.h"
# define GROUP_MASK 0b11110000
# define GRP_SIMPLE 0
# define GRP_REDIR  16
# define GRP_PIPE   32
# define GRP_BIN    48

extern sig_atomic_t	g_signal;

enum	e_token_t
{
	TK_Null, // 0
	TK_String = GRP_SIMPLE | 1, // 1
	TK_Assign = GRP_SIMPLE | 2, // 2
	TK_In = GRP_REDIR | 1,// 17
	TK_Out = GRP_REDIR | 2,// 18
	TK_Append = GRP_REDIR | 3,// 19
	TK_HereDoc = GRP_REDIR | 4,// 20
	TK_Pipe = GRP_PIPE | 1,// 33
	TK_And = GRP_BIN | 1,// 49
	TK_Or = GRP_BIN | 2,// 50
	TK_Number,
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

// DOLLAR ------------------------------------------------------
char	*ft_strjoin_variable(char *s1, char *s2, int i);
char	*case_expand(char *s, int i, t_env **env);
char	*find_variable(char *s, t_env **env);
char	*dollar_handler(char *s, t_env **env);
char	*expand_variable(char *s, int i, t_env **env);
char	*handle_exit_code(void);

// TOKEN -------------------------------------------------------
void	ft_lstadd_back_token(t_token **lst, t_token *new_token);
void	ft_lstclear_token(t_token **lst);

int		lexer(char *line, t_token **head);
t_token	**case_single_char(t_token **head, char character);
t_token	**case_double_char(t_token **head, char character);
t_token	**case_printable(t_token **head, char *line, int *count);
void	case_string_helper2(t_token **token, char *line, int *count);

#endif
