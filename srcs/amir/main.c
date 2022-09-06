/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/09/06 18:08:48 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "minirt.h"
#include "utils.h"
#include "mlx_data.h"
#include "bvh.h"

// ======================= Check parsing ============================

#include <stdio.h>

void	check_value(t_scene scene)
{
	t_list	*check_lights = scene.lights;
	t_list	*check_vols = scene.vols;
	t_list	*check_plane = scene.planes;
	t_cam	cam = scene.cam;
	t_vol	*vol;
	t_plane	*plane;
	t_light	*light;

	if (scene.cam.is_set == true)
		printf("C	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%d\n", cam.pos.x, cam.pos.y, cam.pos.z, cam.vec3.x, cam.vec3.y, cam.vec3.z, cam.h_fov);
	if (scene.ambient)
		printf("A	%.1f		%d,%d,%d\n", scene.ambient->r, scene.ambient->col.r, scene.ambient->col.g, scene.ambient->col.b);
	while (check_lights)
	{
		light = (t_light *)(check_lights->content);
		printf("L	%.1f,%.1f,%.1f	%.1f		%d,%d,%d\n", light->pos.x, light->pos.y, light->pos.z, light->r, light->col.r, light->col.g, light->col.b);
		check_lights = check_lights->next;
	} 
	while (check_vols)
	{
		vol = (t_vol *)(check_vols->content);
		if (vol->type == SPHERE)
			printf("sp	%.1f,%.1f,%.1f	%.1f		%d,%d,%d\n", vol->pos.x, vol->pos.y, vol->pos.z, vol->d, vol->col.r, vol->col.g, vol->col.b);
		if (vol->type == CYLINDER)
			printf("cy	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%.1f		%.1f		%d,%d,%d\n", vol->pos.x, vol->pos.y, vol->pos.z, vol->vec3.x, vol->vec3.y, vol->vec3.z, vol->d, vol->h, vol->col.r, vol->col.g, vol->col.b);
		check_vols = check_vols->next;
	}
	while (check_plane)
	{
		plane = (t_plane *)(check_plane->content);
		printf("pl	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%d,%d,%d\n", plane->pos.x, plane->pos.y, plane->pos.z, plane->vec3.x, plane->vec3.y, plane->vec3.z, plane->col.r, plane->col.g, plane->col.b);
		check_plane = check_plane->next;
	}
}

// =================================================================== */

void	init_scene(t_scene *scene)
{
	scene->vols = NULL;
	scene->lights = NULL;
	scene->ambient = NULL;
	scene->planes = NULL;
	scene->bvh = NULL;
	scene->cam.is_set = false;
}

void	leave_rt(t_scene *scene)
{
	ft_lstclear(&scene->lights, &free);
	ft_lstclear(&scene->vols, &free);
	ft_lstclear(&scene->planes, &free);
	if (scene->ambient)
		free(scene->ambient);
	btree_remove_infix(&scene->bvh, &free);
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
	print_bvh("", scene.bvh, 0);
///*	----> test parse <-----
	check_value(scene);
//	----------------------- */

	graphic_process(&scene);
	leave_rt(&scene);
	return (0);
}
