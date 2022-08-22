/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 00:48:10 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:14:53 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_uint(int fd, unsigned int u, t_format *format)
{
	int	size;

	size = ft_uint_len_base(u, 10);
	size += __precision_len(size, format);
	if (!format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	if (__precision_printf(fd, format))
		return (-1);
	if (u > 0 && __uint_printf(fd, u))
		return (-1);
	if (format->left && __padding_printf(fd, &size, size, format))
		return (-1);
	return (size);
}
