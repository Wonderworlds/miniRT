/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:07:42 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:13:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__hex_printf(int fd, unsigned int nbr, char *base)
{
	if (nbr == 0)
		return (0);
	if (nbr > 15)
	{
		if (__hex_printf(fd, nbr / 16, base))
			return (1);
	}
	if (ft_printf_buffer(fd, base + nbr % 16, 1) < 0)
		return (1);
	return (0);
}

static int	ft_printf_hex_base(int fd, unsigned int nbr, char *base,
		t_format *format)
{
	int	size;
	int	tmp;

	size = ft_uint_len_base(nbr, 16);
	size += __precision_len(size, format);
	if (nbr != 0 && format->alternate == '#')
	{
		if (!format->left && format->padd_char == ' '
			&& __padding_printf(fd, &size, size + 2, format))
			return (-1);
		tmp = ft_printf_buffer(fd, base + 16, 2);
		if (tmp < 0)
			return (-1);
		size += tmp;
		if (!format->left && format->padd_char == '0'
			&& __padding_printf(fd, &size, size, format))
			return (-1);
	}
	else if (!format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	if (__precision_printf(fd, format) || __hex_printf(fd, nbr, base))
		return (-1);
	if (format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	return (size);
}

int	ft_printf_lowhex(int fd, unsigned int u, t_format *format)
{
	return (ft_printf_hex_base(fd, u, "0123456789abcdef0x", format));
}

int	ft_printf_uphex(int fd, unsigned int u, t_format *format)
{
	return (ft_printf_hex_base(fd, u, "0123456789ABCDEF0X", format));
}
