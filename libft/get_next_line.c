/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:22:33 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/10 14:56:16 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

int	free_pbuf(t_pbuf *pbuf)
{
	if (!pbuf->buf)
		return (1);
	free(pbuf->buf);
	pbuf->buf = NULL;
	pbuf->start = 0;
	pbuf->end = 0;
	return (1);
}

char	*apply_buffer(t_pbuf *pbuf, char *end_ptr, int dofree)
{
	size_t	size;
	char	*line;

	size = end_ptr - (pbuf->buf + pbuf->start) + 1;
	if (size < 1 && dofree)
		free_pbuf(pbuf);
	if (size < 1)
		return (NULL);
	line = malloc(size + 1);
	if (!line && free_pbuf(pbuf))
		return (NULL);
	ft_memcpy(line, pbuf->buf + pbuf->start, size);
	line[size] = 0;
	pbuf->start += size;
	if (dofree)
		free_pbuf(pbuf);
	return (line);
}

int	apply_new_data(t_pbuf *pbuf, const char *data, size_t size)
{
	char		*tmp;
	const int	pbufsize = pbuf->end - pbuf->start;

	tmp = malloc(pbufsize + size);
	if (!tmp && free_pbuf(pbuf))
		return (1);
	if (pbufsize > 0)
		ft_memcpy(tmp, pbuf->buf + pbuf->start, pbuf->end - pbuf->start);
	ft_memcpy(tmp + pbufsize, data, size);
	free(pbuf->buf);
	pbuf->buf = tmp;
	pbuf->start = 0;
	pbuf->end = pbufsize + size;
	return (0);
}

static int	handle_read_size(int rs, t_pbuf *pbuf)
{
	if (rs == 0 && !pbuf->buf)
		return (1);
	if (rs != -1)
		return (0);
	free_pbuf(pbuf);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_pbuf	pbuf;
	char			buf[BUFFER_SIZE];
	char			*nl_ptr;
	ssize_t			read_size;

	if (fd == -1)
		free_pbuf(&pbuf);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		nl_ptr = ft_memchr(pbuf.buf + pbuf.start, '\n', pbuf.end - pbuf.start);
		if (nl_ptr)
			return (apply_buffer(&pbuf, nl_ptr, 0));
		read_size = read(fd, buf, BUFFER_SIZE);
		if (handle_read_size(read_size, &pbuf))
			return (NULL);
		if (read_size == 0)
			return (apply_buffer(&pbuf, pbuf.buf + pbuf.end - 1, 1));
		if (apply_new_data(&pbuf, buf, read_size))
			return (NULL);
	}
}
