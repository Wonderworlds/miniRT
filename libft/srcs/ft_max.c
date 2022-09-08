/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:45:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/08 18:22:47 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	maxc(char a, char b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

long	maxl(long a, long b)
{
	if (a >= b)
		return (a);
	return (b);
}

float	maxf(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

double	maxd(double a, double b)
{
	if (a >= b)
		return (a);
	return (b);
}
