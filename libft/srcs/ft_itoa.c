/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 02:23:57 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/18 14:30:44 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strsize(int n, int *minus, unsigned int *tmp)
{
	int				len;

	len = 1;
	*minus = 1;
	if (n < 0)
	{
		*tmp = -n;
		*minus = -1;
		len++;
	}
	else
		*tmp = n;
	while (*tmp >= 10)
	{
		*tmp *= 0.1;
		len++;
	}
	*tmp = n * (*minus);
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	int				minus;
	char			*result;
	unsigned int	tmp;

	len = ft_strsize(n, &minus, &tmp);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = (tmp % 10) + '0';
		tmp *= 0.1;
	}
	if (minus == -1)
		result[0] = '-';
	return (result);
}
