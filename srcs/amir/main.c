/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/08/23 00:02:21 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "minirt.h"
#include "mlx_data.h"
#include <stdio.h>

void	init_scene(t_scene *scene)
{
	scene->vols = NULL;
	scene->lights = NULL;
	scene->cam.is_set = false;
}

int	main(int ac, char **av)
{
	t_scene	scene;
	
	init_scene(&scene);
	if (ac != 2)
	{
		ft_fprintf(2, "Invalid arg\n");
		return (EXIT_FAILURE);
	}
	parse_rt(av[1], &scene);

/*
	t_list	*lights = scene.lights;
//	t_list	*vols = scene.vols;
	t_cam	cam = scene.cam;
//	t_vol	*vol;
	t_light	*light;

	printf("C	%f,%f,%f	%f,%f,%f	%d\n", cam.pos.x, cam.pos.y, cam.pos.z, cam.vec3.x, cam.vec3.y, cam.vec3.z, cam.h_fov);
	while (lights)
	{
		light = lights->content;
		if (light->type == AMB_LIGHT) 
			printf("A	%f		%d,%d,%d\n", light->r, light->col.r, light->col.g, light->col.b);
		else if (light->type == LIGHT) 
			printf("L	%f,%f,%f	%f		%d,%d,%d\n", light->pos.x, light->pos.y, light->pos.z, light->r, light->col.r, light->col.g, light->col.b);
		lights = lights->next;
	} */
	graphic_process(&scene);
	return (0);
}
