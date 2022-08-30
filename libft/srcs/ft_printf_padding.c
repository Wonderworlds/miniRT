/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 22:52:36 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:12:33 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	__padding(t_format *format, const char *str)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	format->padd_size = n;
	return (i);
}

int	__padding_printf(int fd, int *size, int len, t_format *format)
{
	int	i;
	int	n;
	int	tmp;

	i = 0;
	n = 0;
	while (len + i < format->padd_size)
	{
		tmp = ft_printf_buffer(fd, &format->padd_char, 1);
		if (tmp < 0)
			return (1);
		n += tmp;
		i++;
	}
	*size += n;
	return (0);
}
