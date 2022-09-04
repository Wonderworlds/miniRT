/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:56:07 by amahla            #+#    #+#             */
/*   Updated: 2022/09/04 19:02:19 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include "minirt.h"
#include <math.h>

void	create_ray(const t_pos origin, const t_pos dir , t_ray *ray)
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
	float	t;
	t_rgb	color;
	t_hit	hit;
	// int		is_set;

	reset_hit();
	find_plane(scene->planes, &ray);
	if (scene->bvh)
		find_volume(scene->bvh, ray);
	if (get_hit(&hit) != -1)
		return(add_lights(scene, &hit));
// =================== test_color ====================
    t = 0.5*(ray.dir.y + 1.0);
	color.r = 255.999 * ((1.0-t) * 1.0 + t * 0.5);
	color.g = 255.999 * ((1.0-t) * 1.0 + t * 0.7);
	color.b = 255.999 * ((1.0-t) * 1.0 + t * 1.0);
// ===================================================
    return (color);
}

t_rgb	ray_render(int y, int x, t_cam cam, t_scene *scene)
{
	t_ray	ray;
	t_pos	dir;
	double	u;
	double	v;

	u = (double)x / (WIN_WIDTH - 1);
	v = (double)y / (WIN_HEIGHT - 1);
	dir.x = cam.lower_left_corner.x + (u * cam.horizontal.x) + (v * cam.vertical.x) - cam.pos.x;
	dir.y = cam.lower_left_corner.y + (u * cam.horizontal.y) + (v * cam.vertical.y) - cam.pos.y;
	dir.z = cam.lower_left_corner.z + (u * cam.horizontal.z) + (v * cam.vertical.z) - cam.pos.z;
	create_ray(cam.pos, dir, &ray);
	vector_scale(-1, &ray.dir);
	// vector_add(cam.vec3, ray.dir, &ray.dir);
	return (ray_color(ray, scene));
}


