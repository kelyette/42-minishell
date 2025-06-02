/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:22:52 by kcsajka           #+#    #+#             */
/*   Updated: 2025/06/02 12:32:47 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	clean_pipes(int (*fds)[2], int size)
{
	int	i;

	i = -1;
	while (++i < size)
		close_pipe(fds[i]);
	free(fds);
}
