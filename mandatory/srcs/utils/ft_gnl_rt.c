/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:54:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/25 19:51:12 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "utils.h"
#include "libft.h"
#include <unistd.h>

static size_t	gnl_join(char **dest, size_t size_d, char *src, size_t size_s)
{
	size_t	len;
	size_t	j;
	char	*tmp;

	if (size_d + size_s == 0)
		return (0);
	tmp = malloc((size_d + size_s) * sizeof(char));
	if (!tmp)
		return (0);
	len = -1;
	while (++len < size_d)
		tmp[len] = (*dest)[len];
	j = -1;
	while (++j < size_s)
		tmp[len + j] = src[j];
	free(*dest);
	*dest = tmp;
	return (len + j);
}

static size_t	find_newline(const char *s, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*read_fd(size_t *size, t_leftover *leftover, int fd, ssize_t r)
{
	char		*ret;

	ret = NULL;
	*size = gnl_join(&ret, 0, leftover->str, leftover->size);
	if (!ret && leftover->size > 0)
		error_msg("Error\nmalloc: fail\n");
	while (r && !find_newline(ret, *size))
	{
		r = read(fd, leftover->str, BUFFER_SIZE);
		if (r < 0)
		{
			free(ret);
			error_msg("Error\nread: fail\n");
		}
		if (r == 0)
			break ;
		*size = gnl_join(&ret, *size, leftover->str, r);
		if (!ret)
		{
			free(ret);
			error_msg("Error\nmalloc: fail\n");
		}
	}
	return (ret);
}

static int	gnl_leftover(char **newline, size_t size, t_leftover *leftover)
{
	size_t	i_nl;
	size_t	i;
	char	*tmp;

	i_nl = find_newline(*newline, size);
	leftover->size = 0;
	if (i_nl > 0)
	{
		i = -1;
		while (++i + i_nl < size)
			leftover->str[i] = (*newline)[i + i_nl];
		leftover->size = i;
		tmp = NULL;
		size = gnl_join(&tmp, 0, *newline, i_nl);
		if (!tmp)
			return (1);
		free(*newline);
		*newline = tmp;
	}
	gnl_join(newline, size, "\0", 1);
	if (!*newline)
		return (1);
	return (0);
}

char	*ft_gnl_rt(int fd)
{
	static t_leftover	leftover = {{0}, 0};
	char				*newline;
	size_t				size;

	if (fd < 0 || fd > 1023)
		return (NULL);
	size = 0;
	newline = NULL;
	newline = read_fd(&size, &leftover, fd, 1);
	if (newline)
	{
		if (gnl_leftover(&newline, size, &leftover))
		{
			free(newline);
			error_msg("Error\nmalloc: fail\n");
		}
	}
	return (newline);
}
