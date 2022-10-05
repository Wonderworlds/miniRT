/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:23:45 by amahla            #+#    #+#             */
/*   Updated: 2022/08/22 22:02:03 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

bool	pos_format(char *str)
{
	int	i;
	int	axis;

	axis = 4;
	i = 0;
	while (--axis)
	{
		if (str[i] == '-')
			i++;
		if (!ft_isdigit(str[i]))
			break ;
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == '.')
			if (!ft_isdigit(str[++i]))
				break ;
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == ',' && axis > 1)
			i++;
	}
	if (axis || str[i] != ' ')
		return (false);
	return (true);
}

bool	r_format(char *str)
{
	int		i;
	float	n;

	i = 0;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		if (!ft_isdigit(str[++i]))
			return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ' ')
		return (false);
	if (ft_atof(str, &n) || n > 1.0 || n < 0.0)
		return (false);
	return (true);
}

bool	rgb_format(char *str)
{
	int	i;
	int	color;

	color = 4;
	i = 0;
	while (--color)
	{
		if (!ft_isdigit(str[i]))
			break ;
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == ',' && color > 1)
			i++;
	}
	if (color || !(str[i] == ' ' || str[i] == '\n'))
		return (false);
	return (true);
}

bool	h_fov_format(char *str)
{
	int		i;

	i = 0;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ' ' && str[i] != '\0')
		return (false);
	return (true);
}

bool	float_format(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		if (!ft_isdigit(str[++i]))
			return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (!(str[i] == ' ' || str[i] == '\n'))
		return (false);
	return (true);
}
