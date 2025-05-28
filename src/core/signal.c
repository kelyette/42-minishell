/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:34:42 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/28 16:20:42 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change signal type
// code 131 = code 128 +  3 (SIGQUIT)
void	signal_change(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal = 0;
	}
	else if (signal == SIGQUIT) //to update to clean up child process
	{
		printf("Quit (Core dumped)\n");
		exit (131);
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
	if (isatty(STDIN_FILENO))
		sa.sa_handler = SIG_IGN;
	else
		sa.sa_handler = signal_change;
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		return (perror("Error"), 1);
	return (0);
}

