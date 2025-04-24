/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_collectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:27:05 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/24 03:34:12 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "libft.h"

int	collect_cmdctx(t_ctx_cmd *ctx, t_token *data, t_env *env) // TODO
{
	int		size[2];
	t_token	*head;

	if (collect_envp(&ctx->envp, env))
		return (1);
	ctx->argv = NULL;
	ctx->assign = NULL;
	if (!data)
		return (0);
	head = data;
	while (data && data->type == TK_Assign)
		data = data->next;
	ctx->argv = lst_toarr_token(data, );
	ctx->assign = lst_toarr_token(head)
	if (!ctx->argv || !ctx->assign)
		return (1);
	return (0);
}
