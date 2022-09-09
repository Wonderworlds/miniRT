/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_leave.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 23:00:33 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "utils.h"
#include "bvh.h"

static void	free_vols(t_vol *vol)
{
	if (vol->tex && vol->data)
		mlx_destroy_image(vol->data->mlx_ptr, vol->tex->mlx_img);
	if (vol->bump && vol->data)
		mlx_destroy_image(vol->data->mlx_ptr, vol->bump->mlx_img);
	free(vol);
}

static void	free_planes(t_plane *pl)
{
	if (pl->tex && pl->data)
		mlx_destroy_image(pl->data->mlx_ptr, pl->tex->mlx_img);
	if (pl->bump && pl->data)
		mlx_destroy_image(pl->data->mlx_ptr, pl->bump->mlx_img);
	free(pl);
}

void	init_scene(t_scene *scene)
{
	scene->vols = NULL;
	scene->lights = NULL;
	scene->cameras = NULL;
	scene->ambient = NULL;
	scene->planes = NULL;
	scene->line_gnl = NULL;
	scene->bvh = NULL;
	scene->cam = NULL;
	scene->resolut.is_set = false;
}

void	leave_rt(t_scene *scene)
{
	ft_lstclear(&scene->lights, &free);
	ft_lstclear(&scene->vols, &free_vols);
	ft_lstclear(&scene->planes, &free_planes);
	ft_lstclear(&scene->cameras, &free);
	if (scene->ambient)
		free(scene->ambient);
	if (scene->line_gnl)
		free(scene->ambient);
	if (scene->bvh)
		btree_remove_infix(&scene->bvh, &free);
}
