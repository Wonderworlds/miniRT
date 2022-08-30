/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:03:18 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/16 16:02:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s) + 1;
	result = malloc(len * sizeof(char));
	if (!result)
		return (NULL);
	result = ft_memcpy(result, s, len);
	return (result);
}
