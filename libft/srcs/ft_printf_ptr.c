/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:01:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:14:10 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_basehex(unsigned long int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

static int	__longhex_printf(int fd, unsigned long int nbr, char *base)
{
	if (nbr == 0)
		return (0);
	if (nbr > 15)
	{
		if (__longhex_printf(fd, nbr / 16, base))
			return (1);
	}
	if (ft_printf_buffer(fd, base + nbr % 16, 1) < 0)
		return (1);
	return (0);
}

static int	ft_printf_longhex_base(int fd, unsigned long int nbr, char *base,
		t_format *format)
{
	int	size;
	int	tmp;

	size = ft_len_basehex(nbr);
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
	if (__precision_printf(fd, format) || __longhex_printf(fd, nbr, base))
		return (-1);
	if (format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	return (size);
}

int	ft_printf_ptr(int fd, void *ptr, t_format *format)
{
	int	size;
	int	tmp;

	if (ptr)
	{
		format->alternate = '#';
		return (ft_printf_longhex_base(fd, (unsigned long int)ptr,
				"0123456789abcdef0x", format));
	}
	size = 0;
	format->padd_char = ' ';
	if (!format->left && __padding_printf(fd, &size, 5, format))
		return (-1);
	tmp = ft_printf_buffer(fd, "(nil)", 5);
	if (tmp < 0)
		return (-1);
	size += tmp;
	if (format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	return (size);
}
