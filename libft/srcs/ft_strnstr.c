/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:07:17 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/12 23:29:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*bigstr;

	bigstr = (char *)big;
	if (*little == '\0')
		return (bigstr);
	i = 0;
	while (bigstr[i] != '\0' && i < len)
	{
		j = 0;
		while (bigstr[i + j] != '\0' && little[j] != '\0'
			&& bigstr[i + j] == little[j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return (bigstr + i);
		i++;
	}
	return (0);
}
