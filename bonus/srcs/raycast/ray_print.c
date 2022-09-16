/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:56:07 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 18:38:59 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include "minirt.h"
#include <math.h>

void	create_ray(const t_pos origin, const t_pos dir, t_ray *ray)
{
	vector_equal(origin, &ray->origin);
	vector_equal(dir, &ray->dir);
	unit_vector(&ray->dir);
}

int	find_volume(t_bvh *root, t_ray ray)
{
	if (root->vol)
	{
		if (root->vol->type == SPHERE)
			is_sphere_hit(&ray, root->vol);
		if (root->vol->type == CYLINDER)
			is_cylinder_hit(&ray, root->vol);
		if (root->vol->type == TRIANGLE)
			is_triangle_hit(&ray, root->vol);
		if (root->vol->type == CONE)
			is_cone_hit(&ray, root->vol);
	}
	else if (is_aabb_hit(ray, root->box) == true)
	{
		if (root->left)
			find_volume(root->left, ray);
		if (root->right)
			find_volume(root->right, ray);
	}
	return (0);
}

void	find_plane(t_list *pl, t_ray *ray)
{
	if (!pl)
		return ;
	while (pl)
	{
		is_plane_hit(ray, (t_plane *)pl->content);
		pl = pl->next;
	}
}

t_rgb	ray_color(t_ray ray, t_scene *scene)
{
	t_hit	hit;

	reset_hit();
	find_plane(scene->planes, &ray);
	if (scene->bvh)
		find_volume(scene->bvh, ray);
	if (get_hit(&hit) != -1)
		return (add_lights(scene, &hit));
	return (gen_rgb(0, 0, 0));
}

t_rgb	ray_render(int y, int x, t_cam *cam, t_scene *scene)
{
	t_ray		ray;
	t_pos		dir;
	t_couplef	uv;
	int			s;
	t_rgb		color;

	s = 0;
	color = gen_rgb(0, 0, 0);
	while (s++ < scene->resolut.aliasing)
	{
		rand_f(&scene->resolut, s - 1, &uv);
		uv.x += (float)x / (scene->resolut.win_width - 1);
		uv.y += (float)y / (scene->resolut.win_height - 1);
		dir.x = (uv.x * cam->horizontal.x) + (uv.y * cam->vertical.x);
		dir.y = (uv.x * cam->horizontal.y) + (uv.y * cam->vertical.y);
		dir.z = (uv.x * cam->horizontal.z) + (uv.y * cam->vertical.z);
		vector_add(dir, cam->lower_left_corner, &dir);
		vector_sub(dir, cam->pos, &dir);
		create_ray(cam->pos, dir, &ray);
		vector_scale(-1, &ray.dir);
		c_add_color(color, ray_color(ray, scene), &color);
	}
	write_color(&color, &scene->resolut);
	return (color);
}
