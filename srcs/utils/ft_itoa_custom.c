/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:43:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 17:56:53 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_reverse(char *str, size_t size)
{
	size_t	i;

	i = 0;
	if (size < 2)
		return ;
	while (i < size)
	{
		ft_swap(&str[i], &str[size - 1]);
		size--;
		i++;
	}
}

void ft_itoa_custom(int n, char *str, size_t size)
{
	size_t	index;

	index = 0;
	if (n == 0)
		str[index++] = '0';
	while (--size && n > 0)
	{
		str[index++] = n % 10 + '0';
		n /= 10;
	}
	str[index] = 0;
	ft_reverse(str, index);
}