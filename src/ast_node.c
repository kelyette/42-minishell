/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:55 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/10 16:48:36 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_node	*create_node(int type)
{
	t_node	*node;

	node = calloc(1, sizeof(t_node)); // TODO replace forbidden func
	if (!node)
		return (perror("minishell: "), NULL);
	node->type = type;
	return (node);
}

t_node	*create_parent(int type, t_node *lchild, t_node *rchild)
{
	t_node	*node;

	node = create_node(type);
	if (!node)
		return (free_tree(&lchild), free_tree(&rchild), NULL);
	node->lnode = lchild;
	node->rnode = rchild;
	return (node);
}

void	free_tree(t_node **rootptr)
{
	if (!*rootptr)
		return ;
	if ((*rootptr)->lnode)
		free_tree(&(*rootptr)->lnode);
	if ((*rootptr)->rnode)
		free_tree(&(*rootptr)->rnode);
	free(*rootptr);
	*rootptr = NULL;
}