/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:34:42 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/10 04:16:12 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_sigint_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

// Restore parent custom signal handler after child exits
void	restore_sigint_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_change;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

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
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		return (perror("Error"), 1);
	return (0);
}
