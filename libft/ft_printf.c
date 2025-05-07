/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:53:04 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/15 14:04:24 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#include <stdarg.h>

int	g_char_count;

static int	handle_specifier(va_list *value, const char **format)
{
	t_fspec	spec;
	int		parse_rval;

	ft_bzero(&spec, sizeof(spec));
	spec.width = -1;
	spec.precision = -1;
	parse_rval = spec_parse(value, format, &spec);
	if (parse_rval)
		return (parse_rval);
	(*spec.func)(value, &spec);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		tmp_length;

	g_char_count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			handle_specifier(&args, &format);
			continue ;
		}
		fputchar(*format++);
	}
	va_end(args);
	tmp_length = g_char_count;
	g_char_count = 0;
	return (tmp_length);
}
