/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:21:01 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/23 13:54:42 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "libft.h"
#include "stdio.h"

static unsigned int	ft_atof_pre(const char *nptr, float *n)
{
	float			value;
	int				minus;
	unsigned int	index;

	value = 0;
	minus = 1;
	index = 0;
	while (nptr[index] == ' ' || (nptr[index] >= 9 && nptr[index] <= 13))
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			minus = -1;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		if (minus > 0 && (FLT_MAX - nptr[index] + '0') / 10 < value)
			return (0);
		if (minus < 0 && (FLT_MIN + nptr[index] - '0') / 10 > -value)
			return (0);
		value *= 10;
		value += (nptr[index] - '0');
		index++;
	}
	*n = minus * value;
	return (index);
}

int ft_atof(const char *s, float *n)
{
	unsigned int	i;
	unsigned int	n_zero;
	float			dec;
	int				dec_size;

	i = ft_atof_pre(s, n);
	if (!i)
		return (1);
	if (s[i] == '.')
	{
		if (i == FLT_MAX || i == FLT_MIN)
			return (1);
		dec = 0;
		i++;
		n_zero = 0;
		if (s[i] >= '0' && s[i] <= '9')
		{
			while (s[i] == '0')
			{
					i++;
					n_zero++;
			}
			if (!(s[i] >= '0' && s[i] <= '9'))
				return (0);
			if (!ft_atof_pre(&s[i], &dec))
				return (1);
		}
		dec_size = ft_int_len(dec) + n_zero;
		while (dec_size)
		{
			dec /= 10;
			dec_size--;
		}
		*n += dec;
	}
	return (0);
}