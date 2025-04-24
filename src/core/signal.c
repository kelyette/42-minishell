/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:34:42 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/24 16:59:05 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change signal type
void	signal_change(int signal_attribute)
{
	g_signal = signal_attribute;
	if (g_signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 0;
	}
	else if (g_signal == SIGQUIT)
	{
		printf("^\\Quit (Core dumped)\n");
		rl_clear_history();
		exit (0);
	}
}

int	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_change;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) != 0)
		return (perror("Error"), 1);
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		return (perror("Error"), 1);
	return (0);
}
