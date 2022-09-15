/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:21:01 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:20:04 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "libft.h"

static int	ft_atod_pre(const char *nptr, double *n, unsigned int index)
{
	double			value;
	int				minus;

	value = 0;
	minus = 1;
	while (nptr[index] == ' ' || (nptr[index] >= 9 && nptr[index] <= 13))
		nptr++;
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
		if (minus < 0 && (-FLT_MAX + nptr[index] - '0') / 10 > -value)
			return (0);
		value *= 10;
		value += (nptr[index] - '0');
		index++;
	}
	*n = minus * value;
	return (index);
}

static int	ft_atod_suf(const char *s, double *dec, double *n, unsigned int i)
{
	unsigned int	dec_size;
	unsigned int	n_zero;

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
		if ((*n == FLT_MAX || *n == -FLT_MAX) || !ft_atod_pre(&s[i], dec, 0))
			return (1);
	}
	dec_size = ft_int_len(*dec) + n_zero;
	while (dec_size--)
		*dec /= 10;
	return (0);
}

int	ft_atod(const char *s, double *n)
{
	unsigned int	i;
	double			dec;
	int				sign;

	sign = 1;
	if (s[0] == '-')
		sign = -1;
	i = ft_atod_pre(s, n, 0);
	if (!i)
		return (1);
	if (*n != 0 && sign == -1)
		sign = 1;
	if (s[i] == '.')
	{
		i++;
		dec = 0;
		if (ft_atod_suf(&s[i], &dec, n, 0))
			return (1);
		if (*n >= 0)
			*n += dec;
		else
			*n -= dec;
	}
	*n *= sign;
	return (0);
}
