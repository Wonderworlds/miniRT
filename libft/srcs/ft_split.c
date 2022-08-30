/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:32:24 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/18 14:33:15 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_allocate_split(char const *s, char c)
{
	size_t	wcount;
	char	**result;

	wcount = 0;
	while (*s)
	{
		if (*s != c)
		{
			wcount++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	result = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

static char	*ft_strldup(char const *s, size_t len)
{
	char	*result;

	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result = ft_memcpy(result, s, len);
	result[len] = '\0';
	return (result);
}

static void	*ft_free_tab(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static void	*ft_fillsplit(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = 0;
			while (s[i] != c && s[i])
				i++;
			tab[j] = ft_strldup(s, i);
			if (!tab[j])
				return (ft_free_tab(tab, j));
			s += i;
			j++;
		}
		else
			s++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_allocate_split(s, c);
	if (!tab)
		return (NULL);
	if (!(ft_fillsplit(tab, s, c)))
		return (NULL);
	return (tab);
}
