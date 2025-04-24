/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:27:05 by kcsajka           #+#    #+#             */
/*   Updated: 2025/04/24 17:24:05 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "libft.h"

int	collect_cmdctx(t_ctx_cmd *ctx, t_token *data, t_env *env) // TODO
{
	int		asize;
	t_token	*head;

	ctx->envp = env_to_envp(&env);
	ctx->argv = NULL;
	ctx->assign = NULL;
	if (!data)
		return (0);
	head = data;
	asize = 0;
	while (data && data->type == TK_Assign && ++asize)
		data = data->next;
	ctx->argv = lst_toarr_token(data, -1);
	ctx->assign = lst_toarr_token(head, asize);
	if (!ctx->argv || !ctx->assign)
		return (1);
	return (0);
}
