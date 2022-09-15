/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:16:47 by amahla            #+#    #+#             */
/*   Updated: 2022/09/13 00:02:21 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

static t_bool	specular_format(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',')
		return (false);
	i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		if (!ft_isdigit(str[++i]))
			return (false);
	while (ft_isdigit(str[i]))
		i++;
	return (true);
}

size_t	set_specular(t_scene *scene, char *str, t_spec *spec)
{
	size_t	i;

	i = 0;
	if (!specular_format(str))
		exit_parse(scene, NULL);
	if (ft_atoi_err(str, &spec->size) || spec->size < 0 || spec->size > 200)
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i++]))
		;
	if (ft_atof(str + i, &spec->intensity) || spec->intensity < 0
		|| spec->intensity > 2)
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]) || str[i] == '.' || str[i] == ' ')
		i++;
	return (i);
}
