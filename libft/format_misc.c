/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:23:22 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/13 17:49:01 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

static void	fputptr(uintptr_t p)
{
	if (p < 16)
	{
		fputchar(digitc((long)p, 0));
		return ;
	}
	fputptr(p / 16);
	fputchar(digitc((long)(p % 16), 0));
}

void	fmt_ptr(va_list *arg, t_fspec *spec)
{
	uintptr_t	ptr;
	uintptr_t	cptr;
	int			len;

	ptr = (uintptr_t)va_arg(*arg, void *);
	cptr = ptr;
	len = !ptr;
	if (spec->width != -1)
		spec->width -= 2;
	while (cptr != 0 && ++len)
		cptr /= 16;
	if (spec->width != -1 && !spec->ljust)
		fpad(spec->width, len, spec->zpad);
	fputstr("0x");
	fputptr(ptr);
	if (spec->width != -1 && spec->ljust)
		fpad(spec->width, len, 0);
}

void	counter(va_list *arg, t_fspec *spec)
{
	(void)arg;
	(void)spec;
}
