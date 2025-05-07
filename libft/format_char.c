/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:04:59 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/13 15:48:27 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

void	fmt_char(va_list *arg, t_fspec *spec)
{
	char	c;

	if (spec->spec == '%')
		c = '%';
	else
		c = va_arg(*arg, int);
	if (spec->width != -1 && spec->spec == '%' && spec->zpad)
		fpad(spec->width, 1, 1);
	else if (!spec->ljust && spec->width != -1)
		fpad(spec->width, 1, 0);
	fputchar(c);
	if (spec->ljust && spec->width != -1 && !spec->zpad)
		fpad(spec->width, 1, 0);
}

static void	fputstrn(const char *str, int n)
{
	while (n-- > 0)
		fputchar(*str++);
}

void	fmt_str(va_list *arg, t_fspec *spec)
{
	const char	nullstr[] = "(null)";
	char		*str;
	int			len;

	str = va_arg(*arg, char *);
	if (!str)
		str = (char *)nullstr;
	len = ft_strlen(str);
	if (spec->precision != -1 && len > spec->precision)
		len = spec->precision;
	if (!spec->ljust && spec->width != -1)
		fpad(spec->width, len, 0);
	fputstrn(str, len);
	if (spec->ljust && spec->width != -1)
		fpad(spec->width, len, 0);
}
