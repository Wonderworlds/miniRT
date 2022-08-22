/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:54:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/23 23:46:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

size_t	gnl_join(char **dest, size_t size_d, char *src, size_t size_s)
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

size_t	find_newline(const char *s, size_t size)
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

char	*read_fd(size_t *size, t_leftover *leftover, int fd)
{
	ssize_t		r;
	char		*ret;

	ret = NULL;
	*size = gnl_join(&ret, 0, leftover->str, leftover->size);
	if (!ret && leftover->size > 0)
		return (NULL);
	r = 1;
	while (r && !find_newline(ret, *size))
	{
		r = read(fd, leftover->str, BUFFER_SIZE);
		if (r <= 0)
			return (free(ret), NULL);
		if (r == 0)
			break ;
		*size = gnl_join(&ret, *size, leftover->str, r);
		if (!ret)
			return (free(ret), NULL);
	}
	return (ret);
}

int	gnl_leftover(char **newline, size_t size, t_leftover *leftover)
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

char	*ft_gnl(int fd)
{
	static t_leftover	leftover = {{0}, 0};
	char				*newline;
	size_t				size;

	if (fd < 0 || fd > 1023)
		return (NULL);
	size = 0;
	newline = NULL;
	newline = read_fd(&size, &leftover, fd);
	if (newline)
	{
		if (gnl_leftover(&newline, size, &leftover))
			return (free(newline), NULL);
	}
	return (newline);
}
