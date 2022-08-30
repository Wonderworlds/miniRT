/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:55:46 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/12 23:28:52 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*tmp_src;
	char		*tmp_dest;

	if ((dest == src) || n == 0)
		return (dest);
	if (!dest && !src)
		return (0);
	tmp_dest = (char *)dest;
	tmp_src = (const char *)src;
	while (n--)
		tmp_dest[n] = tmp_src[n];
	return (dest);
}
