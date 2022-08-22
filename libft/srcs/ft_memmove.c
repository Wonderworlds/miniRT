/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 00:16:05 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/12 23:28:56 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp_src;
	char	*tmp_dest;

	if ((dest == src) || n == 0)
		return (dest);
	tmp_dest = (char *)dest;
	tmp_src = (char *)src;
	if (tmp_dest > tmp_src)
	{
		while (n--)
			*(tmp_dest + n) = *(tmp_src + n);
		return (dest);
	}
	while (n--)
		*tmp_dest++ = *tmp_src++;
	return (dest);
}
