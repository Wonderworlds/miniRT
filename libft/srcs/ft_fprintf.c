/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:59:04 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:18:35 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

static void	__write(int write_return, int *n)
{
	if (write_return < 0)
		*n = -1;
	else
		*n += write_return;
}

static int	do_convertion(int fd, t_format *format, va_list args)
{
	int	r;

	if (format->convertion == '%')
		r = ft_printf_buffer(fd, "%", 1);
	if (format->convertion == 'c')
		r = ft_printf_char(fd, (char)va_arg(args, int), format);
	if (format->convertion == 's')
		r = ft_printf_str(fd, va_arg(args, char *), format);
	if (format->convertion == 'i' || format->convertion == 'd')
		r = ft_printf_int(fd, va_arg(args, int), format);
	if (format->convertion == 'u')
		r = ft_printf_uint(fd, va_arg(args, unsigned int), format);
	if (format->convertion == 'x')
		r = ft_printf_lowhex(fd, va_arg(args, unsigned int), format);
	if (format->convertion == 'X')
		r = ft_printf_uphex(fd, va_arg(args, unsigned int), format);
	if (format->convertion == 'p')
		r = ft_printf_ptr(fd, va_arg(args, void *), format);
	return (r);
}

int	ft_fprintf(int fd, const char *line, ...)
{
	va_list		args;
	int			i;
	int			len;
	t_format	format;

	if (fd <= 0 || fd > 1023)
		return (-1);
	i = 0;
	len = 0;
	va_start(args, line);
	while (line[i] && len >= 0)
	{
		if (line[i] != '%' || set_format(&format, &line[i], &i))
			__write(ft_printf_buffer(fd, &line[i], 1), &len);
		else
			__write(do_convertion(fd, &format, args), &len);
		i++;
	}
	va_end(args);
	__write(ft_printf_buffer(fd, NULL, -1), &len);
	return (len);
}
