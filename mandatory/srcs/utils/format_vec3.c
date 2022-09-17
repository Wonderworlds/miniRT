/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 00:04:57 by amahla            #+#    #+#             */
/*   Updated: 2022/09/18 01:13:15 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

t_bool	format_float2(char *str, int nb)
{
	int	i;
	int	n;

	i = 0;
	n = ft_atoi(str);
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		if ((n == nb || n == -nb) && str[i] != '0')
			return (false);
		i++;
	}
	return (true);
}
