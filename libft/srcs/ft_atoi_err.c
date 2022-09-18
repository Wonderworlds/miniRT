/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:09:56 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/18 02:49:26 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

/**
 * @brief return the int contained in const char *s
 *
 * @param s const char *
 * @param n ptr to an int which will contain tje int in *s
 * @return 0 if success, 1 if any error
 */
int	ft_atoi_err(const char *s, int *n)
{
	int	minus;

	*n = 0;
	minus = 1;
	if (!s)
		return (1);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			minus = -1;
		s++;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		if (minus > 0 && (INT_MAX - *s + '0') / 10 < *n)
			return (1);
		if (minus < 0 && (INT_MIN + *s - '0') / 10 > -(*n))
			return (1);
		*n *= 10;
		*n += *s - '0';
		s++;
	}
	*n *= minus;
	return (0);
}
