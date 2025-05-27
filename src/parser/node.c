/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:55 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/27 15:18:20 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

int	create_node(t_pctx *ctx, t_node **nodeptr, int type)
{
	*nodeptr = ft_calloc(1, sizeof(t_node));
	if (!*nodeptr)
		return (set_err(ctx, PE_Internal), 1);
	(*nodeptr)->type = type;
	return (0);
}

int	split_node(t_pctx *ctx, t_node **nodeptr, int type)
{
	t_node	*node;

	if (create_node(ctx, &node, type))
		return (free_tree(nodeptr), 1);
	node->lnode = *nodeptr;
	*nodeptr = node;
	return (0);
}

void	free_data(t_token **dataptr)
{
	t_token	*data;
	t_token	*tmp;

	data = *dataptr;
	while (data)
	{
		tmp = data->next;
		free(data->str);
		free(data);
		data = tmp;
	}
	*dataptr = NULL;
}

void	free_tree(t_node **rootptr)
{
	if (!*rootptr)
		return ;
	if ((*rootptr)->lnode)
		free_tree(&(*rootptr)->lnode);
	if ((*rootptr)->rnode)
		free_tree(&(*rootptr)->rnode);
	free_data(&(*rootptr)->data);
	free(*rootptr);
	*rootptr = NULL;
}
