/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/25 17:23:12 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# include "parser.h"
# include "envp.h"

// BUILTINS -------------------------------
int		ft_compare(char *s1, char *s2);

int		builtin_echo(t_node *node, t_env **env);
int		builtin_pwd(t_node *node, t_env **env);
int		builtin_env(t_node *node, t_env **env);
int		builtin_export(t_node *node, t_env **env);
int		builtin_unset(t_node *node, t_env **env);
int		builtin_cd(t_node *node, t_env **env);
t_env	*initiate_oldpwd_env(t_env **env);
int		builtin_exit(t_node *node, t_env **env);
t_env	*get_env_key(t_env **env, char *key);

int		export_assign(char *s, t_env **env);
int		export_no_arg(t_env **env);

#endif
