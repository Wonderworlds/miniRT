/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 01:13:12 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/12 23:29:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;

	if (!size)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i] && dest_len + i < size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (i < size)
		dest[dest_len + i] = '\0';
	if (size < dest_len)
		return (ft_strlen(src) + size);
	return (dest_len + ft_strlen(src));
}
