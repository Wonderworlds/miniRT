/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_rt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:20:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 19:04:49 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_rt(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != ' ')
		i++;
	return (i);
}

size_t	ft_strlen_rt2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != ' ')
		i++;
	return (i);
}
