/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:45:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 18:47:30 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char minc(char a, char b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

long minl(long a, long b)
{
	if (a >= b)
		return (a);
	return (b);
}

float	minf(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

double	mind(double a, double b)
{
	if (a >= b)
		return (a);
	return (b);
}