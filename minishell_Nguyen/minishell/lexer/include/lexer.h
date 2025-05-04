/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:37 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/04 16:54:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# define GROUP_MASK 0b11110000
# define GROUP1     16
# define GROUP2     32
# define GROUP3     48

extern int	g_signal;

enum	e_token_t
{
	TK_Null,
	TK_String,
	TK_Assign,
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

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exported;
	bool			only_key;
	bool			code;
	bool			printed;
	struct s_env	*next;
}	t_env;

// ENVP _____________________________________________________
void	ft_lstadd_back_env(t_env **lst, t_env *new_env);
void	ft_lstclear_env(t_env **lst);
int		ft_lstsize(t_env *lst);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*exception(char *ptr);
char	*malloc_itoa(long n, long count);
int		bit_count(long n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substring_key(char *s);
char	*ft_substring_value(char *s);
int		initiate_base_env(t_env **env);

int		transform_env(t_env **env, char **envp);
char	**env_to_envp(t_env **env);
void	free_envp(char **envp);

// DOLLAR ___________________________________________________
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalnum(int c);

char	*ft_strjoin_variable(char *s1, char *s2, int i);
char	*case_expand(char *s, int i, t_env **env);
char	*find_variable(char *s, t_env **env);
char	*dollar_handler(char *s, t_env **env);
char	*expand_variable(char *s, int i, t_env **env);
char	*handle_exit_code(char *s, int i, t_env **env);

// TOKEN ____________________________________________________
char	*ft_substring(char *s, int len);
char	*ft_strtrim(char *s1, char *set);
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

// SIGNAL ___________________________________________________
int		signal_handler(void);

// EXIT CODE ________________________________________________
int	set_get_code(int code, t_env **env);

#endif
