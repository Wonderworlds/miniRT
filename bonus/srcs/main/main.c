/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/09/13 15:15:38 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "minirt.h"
#include "mlx_data.h"

/*void	check_value(t_scene scene)
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
}*/

#include <stdio.h>

void	check_value2(t_scene *scene)
{
	t_list	*check_vols = scene->vols;
	t_list	*check_plane = scene->planes;
	t_vol	*vol;
	t_plane	*plane;

	printf("resolut->win_width => %d\nresolut->win_height => %d\nresolut->aspect_ratio => %f\n", scene->resolut.win_width, scene->resolut.win_height, scene->resolut.aspect_ratio);
	
	while (check_vols)
	{
		vol = (t_vol *)(check_vols->content);
		if (vol->type == TRIANGLE)
			printf("tr	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%d,%d,%d	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	texture:%s bumpmap:%s ", vol->tr[0].x, vol->tr[0].y, vol->tr[0].z, vol->tr[1].x, vol->tr[1].y, vol->tr[1].z, vol->tr[2].x, vol->tr[2].y, vol->tr[2].z, vol->col.r, vol->col.g, vol->col.b, vol->pos.x, vol->pos.y, vol->pos.z, vol->vec3.x, vol->vec3.y, vol->vec3.z, ((vol->tex) ? "Yes" : "No"), ((vol->bump) ? "Yes" : "No"));
		if (vol->disruption == NONE)
			printf("disruption:none\n");
		if (vol->disruption == CHECKERBOARD)
			printf("disruption:checkerboard\n");
		if (vol->disruption == OTHER)
			printf("disruption:other\n");
		check_vols = check_vols->next;
	}
		
	while (check_plane)
	{
		plane = (t_plane *)(check_plane->content);
		printf("pl	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%d,%d,%d	texture:%s bumpmap:%s ", plane->pos.x, plane->pos.y, plane->pos.z, plane->vec3.x, plane->vec3.y, plane->vec3.z, plane->col.r, plane->col.g, plane->col.b, ((plane->tex) ? "Yes" : "No"), ((plane->bump) ? "Yes" : "No"));
		if (plane->disruption == NONE)
			printf("disruption:none\n");
		if (plane->disruption == CHECKERBOARD)
			printf("disruption:checkerboard\n");
		if (plane->disruption == OTHER)
			printf("disruption:other\n");
		check_plane = check_plane->next;
	}
}

int	main(int ac, char **av)
{
	t_scene	scene;

	init_scene(&scene);
	if (ac != 2)
	{
		if (ac < 2)
			ft_fprintf(2, "Error\nMaps needed\n");
		else
			ft_fprintf(2, "Error\nToo many maps to load\nPlease choose one\n");
		return (EXIT_FAILURE);
	}
	parse_rt(av[1], &scene);
//	========== test parse =========
//	check_value2(&scene);
//	==============================
//
	ft_printf("Done\n");
	graphic_process(&scene);
	return (EXIT_SUCCESS);
}
