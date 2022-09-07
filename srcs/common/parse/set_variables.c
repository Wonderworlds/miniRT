/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/07 20:04:59 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

int	set_pos(t_scene *scene, t_pos *pos, char *str)
{
	int	i;
	int	times;

	i = 0;
	times = 4;
	if (!pos_format(str))
		exit_parse(scene, NULL);
	while (--times)
	{
		if (times == 3 && ft_atof(str + i, &pos->x))
			exit_parse(scene, NULL);
		else if (times == 2 && ft_atof(str + i, &pos->y))
			exit_parse(scene, NULL);
		else if (times == 1 && ft_atof(str + i, &pos->z))
			exit_parse(scene, NULL);
		while (ft_isdigit(str[i]) || str[i] == '.' || str[i] == '-')
			i++;
		if (str[i] == ',')
			i++;
	}
	return (i);
}

int	set_vec3(t_scene *scene, t_pos *vec3, char *str)
{
	int	i;
	int	times;

	i = 0;
	times = 4;
	if (!pos_format(str))
		exit_parse(scene, NULL);
	while (--times)
	{
		if (times == 3 && ft_atof(str + i, &vec3->x) && vec3->x >= -1.0
			&& vec3->y <= 1.0)
			exit_parse(scene, NULL);
		else if (times == 2 && ft_atof(str + i, &vec3->y) && vec3->y >= -1.0
			&& vec3->y <= 1.0)
			exit_parse(scene, NULL);
		else if (times == 1 && ft_atof(str + i, &vec3->z) && vec3->z >= -1.0
			&& vec3->z <= 1.0)
			exit_parse(scene, NULL);
		while (ft_isdigit(str[i]) || str[i] == '.' || str[i] == '-')
			i++;
		if (str[i] == ',')
			i++;
	}
	return (i);
}

int	set_rgb(t_scene *scene, t_rgb *col, char *str)
{
	int	i;
	int	times;

	i = 0;
	times = 4;
	if (!rgb_format(str))
		exit_parse(scene, NULL);
	while (--times)
	{
		if (times == 3 && (ft_atoi_err(str + i, &col->r) || col->r < 0
				|| col->r > 255))
			exit_parse(scene, NULL);
		else if (times == 2 && (ft_atoi_err(str + i, &col->g) || col->g < 0
				|| col->g > 255))
			exit_parse(scene, NULL);
		else if (times == 1 && (ft_atoi_err(str + i, &col->b) || col->b < 0
				|| col->b > 255))
			exit_parse(scene, NULL);
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == ',')
			i++;
	}
	return (i);
}

int	set_float(t_scene *scene, float *data, char *str)
{
	int	i;

	i = 0;
	if (!float_format(str + i) || ft_atof(str + i, data))
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]) || str[i] == '.')
		i++;
	return (i);
}

int	set_h_fov(t_scene *scene, int *data, char *str)
{
	int	i;

	i = 0;
	if (!float_format(str + i) || ft_atoi_err(str + i, data) || *data <= 0
		|| *data > 180)
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}
