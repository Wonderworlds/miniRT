/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/08/30 16:15:59 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"
#include "mlx_data.h"
#include "utils.h"

void	camera(t_scene *scene, char *str)
{
	int		i;

	i = 1;
	if (scene->cam.is_set == true)
		exit_parse(scene);
	scene->cam.is_set = true;
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &scene->cam.pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_vec3(scene, &scene->cam.vec3, str + i);
	while (str[i] == ' ')
		i++;
	set_vector(0.0, 0.0, 0.0, &scene->cam.origin);
	set_vector(VIEWPORT_WIDHT, 0.0, 0.0, &scene->cam.horizontal);
	set_vector(0.0, VIEWPORT_HEIGHT, 0.0, &scene->cam.vertical);
	scene->cam.lower_left_corner.x = scene->cam.origin.x - VIEWPORT_WIDHT / 2;  
	scene->cam.lower_left_corner.y = scene->cam.origin.y - VIEWPORT_HEIGHT / 2;  
	scene->cam.lower_left_corner.z = scene->cam.origin.z - FOCAL_LENGHT;  

	i += set_h_fov(scene, &scene->cam.h_fov, str + i);
}
