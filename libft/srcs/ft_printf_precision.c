/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 23:04:51 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:12:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	__precision(t_format *format, const char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (str[i] != '.')
		return (0);
	format->has_precision = 1;
	format->padd_char = ' ';
	i++;
	if (str[i] == '-')
	{
		format->precision = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	if (format->precision == -1)
		format->precision = 1;
	else
		format->precision = n;
	return (i);
}

int	__precision_len(int len, t_format *format)
{
	if (len > format->precision)
		format->precision = 0;
	else
		format->precision -= len;
	return (format->precision);
}

int	__precision_printf(int fd, t_format *format)
{
	int	i;

	i = 0;
	while (i < format->precision)
	{
		if (ft_printf_buffer(fd, "0", 1) < 0)
			return (1);
		i++;
	}
	return (0);
}
