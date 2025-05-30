/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:15:04 by kcsajka           #+#    #+#             */
/*   Updated: 2025/05/28 17:09:54 by hoannguy         ###   ########.fr       */
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
# include "libft.h"
# define ERRPREFIX "minishell"

int		signal_handler(void);
void	signal_change(int signal);
void 	disable_sigint_handler(void);
void 	restore_sigint_handler(void);

typedef enum e_status
{
	MS_OK = 0,
	MS_ERROR = 1,
	MS_BAD_USAGE = 2,
	MS_NO_EXEC = 126,
	MS_CMD_NOT_FOUND = 127,
}	t_ec;

void	print_error(int err, const char *msg, const char *data);

#endif
