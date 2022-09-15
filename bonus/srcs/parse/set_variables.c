/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/15 18:56:59 by fmauguin         ###   ########.fr       */
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
		if (times == 3 && (ft_atod(str + i, &pos->x) || pos->x > 10000
				|| pos->x < -10000))
			exit_parse(scene, NULL);
		else if (times == 2 && (ft_atod(str + i, &pos->y) || pos->y > 10000
				|| pos->y < -10000))
			exit_parse(scene, NULL);
		else if (times == 1 && (ft_atod(str + i, &pos->z) || pos->z > 10000
				|| pos->z < -10000))
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
		if (times == 3 && (ft_atod(str + i, &vec3->x) || vec3->x < -1
				|| vec3->x > 1))
			exit_parse(scene, NULL);
		else if (times == 2 && (ft_atod(str + i, &vec3->y) || vec3->y < -1
				|| vec3->y > 1))
			exit_parse(scene, NULL);
		else if (times == 1 && (ft_atod(str + i, &vec3->z) || vec3->z < -1
				|| vec3->z > 1))
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

int	set_float(t_scene *scene, double *data, char *str, int option)
{
	int	i;

	i = 0;
	if (!float_format(str + i) || ft_atod(str + i, data))
		exit_parse(scene, NULL);
	if (option == 0 && (*data < 0.f || *data > 1.f))
		exit_parse(scene, NULL);
	else if (option == 1 && (*data < 0.f || *data > 10000.f))
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]) || str[i] == '.')
		i++;
	return (i);
}

int	set_h_fov(t_scene *scene, int *data, char *str)
{
	int	i;

	i = 0;
	if (!h_fov_format(str + i) || ft_atoi_err(str + i, data) || *data <= 0
		|| *data > 180)
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}
