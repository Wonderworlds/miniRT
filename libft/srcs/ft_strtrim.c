/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:13:15 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/20 13:11:21 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (*s1)
	{
		while (s1[i])
			i++;
		while (i >= 1 && ft_strchr(set, s1[i - 1]))
			i--;
	}
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	j = -1;
	while (++j < i)
		result[j] = s1[j];
	result[j] = '\0';
	return (result);
}
