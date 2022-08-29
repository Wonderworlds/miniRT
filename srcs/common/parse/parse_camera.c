/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/08/29 16:48:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

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
	i += set_h_fov(scene, &scene->cam.h_fov, str + i);
}
