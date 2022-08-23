/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:21:01 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/23 16:00:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "libft.h"

static int	ft_atof_pre(const char *nptr, float *n, unsigned int index)
{
	float			value;
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

static int	ft_atof_suf(const char *s, float *dec, float *n, unsigned int i)
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
		if ((*n == FLT_MAX || *n == -FLT_MAX) || !ft_atof_pre(&s[i], dec, 0))
			return (1);
	}
	dec_size = ft_int_len(*dec) + n_zero;
	while (dec_size--)
		*dec /= 10;
	return (0);
}

int	ft_atof(const char *s, float *n)
{
	unsigned int	i;
	float			dec;

	i = ft_atof_pre(s, n, 0);
	if (!i)
		return (1);
	if (s[i] == '.')
	{
		i++;
		dec = 0;
		if (ft_atof_suf(&s[i], &dec, n, 0))
			return (1);
		if (*n >= 0)
			*n += dec;
		else
			*n -= dec;
	}
	return (0);
}
