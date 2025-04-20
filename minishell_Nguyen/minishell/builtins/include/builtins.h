/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/20 18:34:27 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

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

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

int		builtin_echo(t_node *node);
int		builtin_pwd(void);
void	builtin_env(char **envp);
#endif