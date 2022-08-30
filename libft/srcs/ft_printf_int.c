/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 00:09:21 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:13:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	__uint_printf(int fd, unsigned int n)
{
	char	*digits;

	digits = "0123456789";
	if (n > 9 && __uint_printf(fd, n / 10))
		return (1);
	if (ft_printf_buffer(fd, &digits[n % 10], 1) < 0)
		return (1);
	return (0);
}

static int	__sign_printf(int fd, int n, t_format *format)
{
	if (n < 0)
	{
		if (ft_printf_buffer(fd, "-", 1) < 0)
			return (1);
	}
	else
	{
		if (format->sign == 1 && ft_printf_buffer(fd, " ", 1) < 0)
			return (1);
		if (format->sign == 2 && ft_printf_buffer(fd, "+", 1) < 0)
			return (1);
	}
	return (0);
}

int	ft_printf_int(int fd, int n, t_format *format)
{
	int	size;

	size = ft_int_len(n);
	size += __precision_len(size, format);
	if (n < 0 || (n >= 0 && format->sign))
		size++;
	if (!format->left)
	{
		if (format->padd_char == '0' && __sign_printf(fd, n, format))
			return (-1);
		if (__padding_printf(fd, &size, size, format))
			return (-1);
		if (format->padd_char == ' ' && __sign_printf(fd, n, format))
			return (-1);
	}
	else if (__sign_printf(fd, n, format))
		return (-1);
	if (__precision_printf(fd, format))
		return (-1);
	if ((n > 0 && __uint_printf(fd, n)) || (n < 0 && __uint_printf(fd, -n)))
		return (-1);
	if (format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	return (size);
}
