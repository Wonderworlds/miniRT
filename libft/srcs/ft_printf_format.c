/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 22:22:11 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/29 17:12:30 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	__convertion(char c)
{
	if (c == '%' || c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

static void	reset_format(t_format *format)
{
	format->convertion = 0;
	format->alternate = 0;
	format->padd_char = ' ';
	format->left = 0;
	format->padd_size = 0;
	format->has_precision = 0;
	format->precision = 1;
	format->sign = 0;
}

static void	__flags(char c, t_format *format)
{
	if (c == '#')
		format->alternate = c;
	if (c == '0' && format->left == 0)
		format->padd_char = c;
	if (c == '-')
	{
		format->padd_char = ' ';
		format->left = 1;
	}
	if (c == ' ' && !format->sign)
		format->sign = 1;
	if (c == '+')
		format->sign = 2;
}

int	set_format(t_format *format, const char *str, int *index)
{
	int	i;

	reset_format(format);
	i = 1;
	while (str[i] && (str[i] == '#' || str[i] == '0' || str[i] == '-'
			|| str[i] == ' ' || str[i] == '+'))
	{
		__flags(str[i], format);
		i++;
	}
	i += __padding(format, &str[i]);
	i += __precision(format, &str[i]);
	if (!__convertion(str[i]))
		return (1);
	format->convertion = str[i];
	*index += i;
	return (0);
}
