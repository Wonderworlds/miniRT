/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 23:25:04 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:12:44 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_char(int fd, char c, t_format *format)
{
	int	size;
	int	r_printf;

	size = 0;
	format->padd_char = ' ';
	if (!format->left && __padding_printf(fd, &size, 1, format))
		return (-1);
	r_printf = ft_printf_buffer(fd, &c, 1);
	if (r_printf < 0)
		return (-1);
	size += r_printf;
	if (format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	return (size);
}
