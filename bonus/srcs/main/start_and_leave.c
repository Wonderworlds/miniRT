/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_leave.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 00:26:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "utils.h"
#include "bvh.h"

static void	free_vols(void *ptr)
{
	t_vol	*vol;

	vol = (t_vol *)ptr;
	if (vol->tex)
	{
		if (vol->tex->img && vol->data)
			mlx_destroy_image(vol->data->mlx_ptr, vol->tex->img);
		if (vol->tex->file)
			free(vol->tex->file);
		free(vol->tex);
	}
	if (vol->bump && vol->data)
	{
		if (vol->bump->img && vol->data)
			mlx_destroy_image(vol->data->mlx_ptr, vol->bump->img);
		if (vol->bump->file)
			free(vol->bump->file);
		free(vol->bump);
	}
	free(vol);
}

static void	free_planes(void *ptr)
{
	t_plane	*pl;

	pl = (t_plane *)ptr;
	if (pl->tex)
	{
		if (pl->tex->img == NULL && pl->data)
			mlx_destroy_image(pl->data->mlx_ptr, pl->tex->img);
		if (pl->tex->file)
			free(pl->tex->file);
		free(pl->tex);
	}
	if (pl->bump && pl->data)
	{
		if (pl->bump->img && pl->data)
			mlx_destroy_image(pl->data->mlx_ptr, pl->bump->img);
		if (pl->bump->file)
			free(pl->bump->file);
		free(pl->bump);
	}
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
		free(scene->line_gnl);
	if (scene->bvh)
		btree_remove_infix(&scene->bvh, &free);
}
