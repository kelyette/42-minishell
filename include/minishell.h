/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:15:04 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/09 16:17:31 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# define ERRPREFIX "minishell"

extern sig_atomic_t	g_signal;

int		signal_handler(void);

enum e_status
{
	MS_OK = 0,
	MS_ERROR = 1,
	MS_BAD_USAGE = 2,
	MS_NO_EXEC = 126,
	MS_CMD_NOT_FOUND = 127,
};

void	print_error(int err, const char *msg, const char *data);

#endif
