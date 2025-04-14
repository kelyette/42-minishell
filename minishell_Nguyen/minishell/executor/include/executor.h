/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:50:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/14 11:24:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

void	case_operator(t_node *tree, int *i);
void	case_pipe(t_node *tree, int *i);
void	case_redirection(t_node *tree, int *i);
void	case_cmd(t_node *tree, int *i);

#endif