/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:57:34 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/20 13:13:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	uc;

	uc = c;
	ptr = 0;
	while (*s)
	{
		if (*s == uc)
			ptr = (char *)s;
		s++;
	}
	if (*s == uc)
		ptr = (char *)s;
	return (ptr);
}
