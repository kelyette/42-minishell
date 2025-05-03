/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/03 15:24:46 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

// to delete after
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

// to delete after
enum	e_node_t
{
	NT_Cmd = 1,
};

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_node
{
	int				type;
	struct s_node	*lnode;
	struct s_node	*rnode;
	t_token			*data;
}	t_node;

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

// ENVP ----------------------------------
void	ft_lstadd_back_env(t_env **lst, t_env *new_env);
void	ft_lstclear_env(t_env **lst);
int		ft_lstsize(t_env *lst);
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

// BUILTINS -------------------------------
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_compare(char *s1, char *s2);
void	ft_lstdelone_env(t_env *lst);

int		builtin_echo(t_node *node);
int		builtin_pwd(void);
int		builtin_env(t_env **env);
int		builtin_export(t_node *node, t_env **env);
int		export_no_arg(t_env **env);
int		builtin_unset(t_node *node, t_env **env);
int		builtin_cd(t_node *node, t_env **env);
t_env	*find_pwd(t_env **env);
t_env	*find_oldpwd(t_env **env);
t_env	*find_home(t_env **env);
#endif