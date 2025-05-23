/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:31:00 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/14 14:44:42 by kcsajka          ###   ########.fr       */
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
	bool			only_key;
	bool			code;
	bool			printed;
	struct s_env	*next;
}	t_env;

void	ft_lstadd_back_env(t_env **lst, t_env *new_env);
void	ft_lstclear_env(t_env **lst);
void	ft_lstdelone_env(t_env *lst);
int		ft_lstsize_env(t_env *lst);
char	*ft_substring_key(char *s);
char	*ft_substring_value(char *s);
int		initiate_base_env(t_env **env);

int		transform_env(t_env **env, char **envp);
char	**env_to_envp(t_env **env);
void	free_envp(char **envp);
int		set_get_code(int code, t_env **env);

t_env	*get_env_key(const t_env *env, char *key);

#endif
