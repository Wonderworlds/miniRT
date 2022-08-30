/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/08/27 16:57:11 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "mlx_data.h"

// ======================= Check parsing ============================

#include <stdio.h>

void	check_value(t_scene scene)
{
	t_list	*check_lights = scene.lights;
	t_list	*check_vols = scene.vols;
	t_cam	cam = scene.cam;
	t_vol	*vol;
	t_light *light;

	if (scene.cam.is_set == true)
		printf("C	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%d\n", cam.pos.x, cam.pos.y, cam.pos.z, cam.vec3.x, cam.vec3.y, cam.vec3.z, cam.h_fov);
	while (check_lights)
	{
		light = (t_light *)(check_lights->content);
		if (light->type == AMB_LIGHT) 
			printf("A	%.1f		%d,%d,%d\n", light->r, light->col.r, light->col.g, light->col.b);
		else if (light->type == LIGHT) 
			printf("L	%.1f,%.1f,%.1f	%.1f		%d,%d,%d\n", light->pos.x, light->pos.y, light->pos.z, light->r, light->col.r, light->col.g, light->col.b);
		check_lights = check_lights->next;
	} 
	while (check_vols)
	{
		vol = (t_vol *)(check_vols->content);
		if (vol->type == SPHERE)
			printf("sp	%.1f,%.1f,%.1f	%.1f		%d,%d,%d\n", vol->pos.x, vol->pos.y, vol->pos.z, vol->d, vol->col.r, vol->col.g, vol->col.b);
		if (vol->type == PLANE)
			printf("pl	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%d,%d,%d\n", vol->pos.x, vol->pos.y, vol->pos.z, vol->vec3.x, vol->vec3.y, vol->vec3.z, vol->col.r, vol->col.g, vol->col.b);
		if (vol->type == CYLINDER)
			printf("cy	%.1f,%.1f,%.1f	%.1f,%.1f,%.1f	%.1f		%.1f		%d,%d,%d\n", vol->pos.x, vol->pos.y, vol->pos.z, vol->vec3.x, vol->vec3.y, vol->vec3.z, vol->d, vol->h, vol->col.r, vol->col.g, vol->col.b);
		check_vols = check_vols->next;
	}
}

// =================================================================== */

void	init_scene(t_scene *scene, t_list **lights, t_list **vols)
{
	*lights = NULL;
	*vols = NULL;
	scene->vols = *vols;
	scene->lights = *lights;
	scene->cam.is_set = false;
}

void	leave_rt(t_scene *scene)
{
	ft_lstclear(&scene->lights, &free);
	ft_lstclear(&scene->vols, &free);
}

int	main(int ac, char **av)
{
	t_scene	scene;
	t_list	*lights;
	t_list	*vols;
	t_box	box_total;
	t_box	box_left;
	t_box	box_right;
	unsigned int	m;

	init_scene(&scene, &lights, &vols);
	if (ac != 2)
	{
		ft_fprintf(2, "Invalid arg\n");
		return (EXIT_FAILURE);
	}
	parse_rt(av[1], &scene);

///*	----> test parse <-----
	check_value(scene);
//	----------------------- */

ft_lstiter(scene.vols, print_vol);
bounds_total(scene.vols, &box_total, 0, ft_lstsize(scene.vols) - 1);
m = sort_vols(&scene.vols, &box_total);
ft_printf("\nm = %u\n", m);
ft_lstiter(scene.vols, print_vol);
bounds_total(scene.vols, &box_left, 0, m - 1);
bounds_total(scene.vols, &box_right, m, ft_lstsize(scene.vols) - 1);
ft_fprintf(2, "\nbounds left\n");
print_pos(&box_left.center, "center box");
print_pos(&box_left.min, "   min box");
print_pos(&box_left.max, "   max box");
ft_fprintf(2, "\nbounds right\n");
print_pos(&box_right.center, "center box");
print_pos(&box_right.min, "   min box");
print_pos(&box_right.max, "   max box");
///*	----> test bvh <-----
//	----------------------- */

	// graphic_process(&scene);
	// leave_rt(&scene);
	return (0);
}
