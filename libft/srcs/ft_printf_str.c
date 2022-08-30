/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 23:43:25 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:14:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size_max(char *str, t_format *format)
{
	if (!str && format->has_precision && format->precision < 6)
		return (0);
	else if (!str)
		return (6);
	else if (format->has_precision)
		return (ft_strnlen(str, format->precision));
	else
		return (ft_strlen(str));
	return (0);
}

int	ft_printf_str(int fd, char *str, t_format *format)
{
	int	size;
	int	size_max;
	int	r_printf;

	format->padd_char = ' ';
	size_max = get_size_max(str, format);
	size = 0;
	if (!format->left && __padding_printf(fd, &size, size_max, format))
		return (-1);
	if (!str)
		r_printf = ft_printf_buffer(fd, "(null)", size_max);
	else
		r_printf = ft_printf_buffer(fd, str, size_max);
	if (r_printf < 0)
		return (-1);
	size += r_printf;
	if (format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	return (size);
}
