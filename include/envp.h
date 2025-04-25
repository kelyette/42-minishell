/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:31:00 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/25 18:27:44 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H
# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env;

void	ft_lstadd_back_env(t_env **lst, t_env *new_env);
void	ft_lstclear_env(t_env **lst);
int		ft_lstsize(t_env *lst);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substring_key(char *s);
char	*ft_substring_value(char *s);

int		transform_env(t_env **env, char **envp);
char	**env_to_envp(t_env **env);
void	free_envp(char **envp);

#endif
