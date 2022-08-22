/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 21:31:35 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:12:28 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	write_buffer(int fd, char *buffer, int *size)
{
	int	r;

	r = write(fd, buffer, *size);
	*size = 0;
	if (r < 0)
		return (1);
	return (0);
}

int	ft_printf_buffer(int fd, const char *str, int size)
{
	static char	buffer[WRITE_BUFFER];
	static int	__len = 0;
	int			i;

	if (!str)
	{
		if (__len == 0)
			return (0);
		if (write_buffer(fd, buffer, &__len))
			return (-1);
		return (0);
	}
	i = -1;
	while (++i < size)
	{
		if (__len < WRITE_BUFFER)
		{
			buffer[__len] = str[i];
			__len++;
		}
		else if (write_buffer(fd, buffer, &__len))
			return (-1);
	}
	return (size);
}
