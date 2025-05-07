/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:46:08 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/25 14:01:00 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

int	expect_flags(const char **format, t_fspec *spec)
{
	const char	ftable[] = "\\-+ #0";
	int			flagbit;
	int			flags;

	flags = 0;
	while (ft_strchr(ftable, **format))
	{
		flagbit = 1 << (ft_strchr(ftable, **format) - 1 - ftable);
		if (flagbit < 1)
			break ;
		flags |= flagbit;
		++*format;
	}
	spec->ljust = flags & (1 << 0);
	spec->psign = flags & (1 << 1);
	spec->fillsign = flags & (1 << 2) & !spec->psign;
	spec->hexprefix = flags & (1 << 3);
	spec->zpad = flags & (1 << 4) & !spec->ljust;
	return (0);
}

int	expect_width(va_list *arg, const char **format, t_fspec *spec)
{
	const char	*str = *format;
	int			width;

	width = 0;
	if (*str == '*')
	{
		str++;
		width = va_arg(*arg, int);
		if (width < 0)
		{
			if (width == INT_MIN)
				width = INT_MAX;
			else
				width = -width;
			spec->ljust = 1;
			spec->zpad = 0;
		}
	}
	else if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		width = width * 10 + (*str++ - '0');
	spec->width = width;
	*format = str;
	return (0);
}

int	expect_precision(va_list *arg, const char **format, t_fspec *spec)
{
	const char	*str = *format;
	int			precision;

	if (*str++ != '.')
		return (0);
	precision = 0;
	spec->precision = 0;
	if (*str == '*')
	{
		spec->precision = va_arg(*arg, int);
		*format = ++str;
		return (0);
	}
	while (ft_isdigit(*str))
		precision = precision * 10 + (*str++ - '0');
	spec->precision = precision;
	*format = str;
	return (0);
}

int	expect_specifier(const char **format, t_fspec *spec)
{
	static const char		*spec_char[] = {"diuxXb", "p", "c%", "s", "n"};
	static const t_ffptr	spec_func[] = {
		&fmt_int, &fmt_ptr, &fmt_char, &fmt_str, &counter
	};
	int						i;

	i = sizeof(spec_func) / sizeof(spec_func[0]);
	while (i-- > 0)
	{
		if (ft_strchr(spec_char[i], **format))
		{
			spec->spec = **format;
			(*format)++;
			spec->func = spec_func[i];
			return (0);
		}
	}
	return (1);
}

int	spec_parse(va_list *arg, const char **format, t_fspec *spec)
{
	if (expect_flags(format, spec))
		return (1);
	if (expect_width(arg, format, spec))
		return (2);
	if (expect_precision(arg, format, spec))
		return (3);
	if (expect_specifier(format, spec))
		return (4);
	if (!ULIMIT)
		return (0);
	if (spec->width > ULIMIT)
		spec->width = ULIMIT;
	if (spec->precision > ULIMIT)
		spec->precision = ULIMIT;
	if (spec->spec != '%' && spec->precision != -1 && spec->zpad)
		spec->zpad = 0;
	return (0);
}
