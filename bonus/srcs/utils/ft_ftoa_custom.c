/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:43:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:10:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

static void	ft_ftoa_custom2(char *str, size_t i)
{
	if (i == 1)
	{
		str[3] = 0;
		str[2] = str[0];
		str[1] = '.';
		str[0] = '0';
	}
	else
	{
		str[i + 1] = 0;
		str[i] = str[i - 1];
		str[--i] = '.';
	}
}

void	ft_ftoa_custom(double n, char *str, size_t size)
{
	size_t	i;

	i = 0;
	n *= 10;
	ft_itoa_custom(n, str, size);
	i = ft_strlen(str);
	if (i == 2 && str[0] == '-')
	{
		str[4] = 0;
		str[3] = str[1];
		str[2] = '.';
		str[1] = '0';
	}
	else
		ft_ftoa_custom2(str, i);
}
