/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/10 03:39:29 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "minirt.h"

void	exit_graphic(t_data *data, const char *error)
{
	if (error)
		ft_fprintf(2, "%s", error);
	leave_rt(data->scene);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// mlx_destroy_display(data->mlx_ptr); SEG FAULT ?
	free(data->mlx_ptr);
	exit(EXIT_FAILURE);
}

static void	load_xpm_pl(t_data *data, t_plane *pl)
{
	if (pl && pl->tex)
	{
		pl->tex->img = mlx_xpm_file_to_image(data->mlx_ptr,
			pl->tex->file, &pl->tex->h, &pl->tex->w);
		free(pl->tex->file);
		pl->tex->file = NULL;
		if (!pl->tex->img)
			exit_graphic(data, "Error\nLoad xpm fail\n");
	}
	if (pl && pl->bump)
	{
		pl->bump->img = mlx_xpm_file_to_image(data->mlx_ptr,
			pl->bump->file, &pl->bump->h, &pl->bump->w);
		free(pl->bump->file);
		pl->bump->file = NULL;
		if (!pl->bump->img)
			exit_graphic(data, "Error\nLoad xpm fail\n");
	}
}

static void	load_xpm_vol(t_data *data, t_vol *vol)
{
	if (vol && vol->tex)
	{
		vol->tex->img = mlx_xpm_file_to_image(data->mlx_ptr,
			vol->tex->file, &vol->tex->h, &vol->tex->w);
		free(vol->tex->file);
		vol->tex->file = NULL;
		if (!vol->tex->img)
			exit_graphic(data, "Error\nLoad xpm fail\n");
	}
	if (vol && vol->bump)
	{
		vol->bump->img = mlx_xpm_file_to_image(data->mlx_ptr,
			vol->bump->file, &vol->bump->h, &vol->bump->w);
		free(vol->bump->file);
		vol->bump->file = NULL;
		if (!vol->bump->img)
			exit_graphic(data, "Error\nLoad xpm fail\n");
	}
}

static void	init_texture_menu(t_data *data, t_list *pl, t_list *vol)
{
	while (vol)
	{
		load_xpm_vol(data, vol->content);
		vol = vol->next;
	}
	while (pl)
	{
		load_xpm_pl(data, pl->content);
		pl = pl->next;
	}
	data->menu.is_visible = false;
	data->menu.has_changed = false;
	data->menu.index = 0;
	data->menu.item = 0;
	data->menu.field_index = 0;
	data->menu.max_f_index = 0;
	ft_memset(&data->menu.bprint, 0, 15);
}

int	graphic_process(t_scene *scene)
{
	t_data	data;

	data.scene = scene;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		error_mlx_data(&data, NULL);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data.win_ptr)
		error_mlx_data(&data, data.mlx_ptr);
	mlx_set_font(data.mlx_ptr, data.win_ptr, "9x15bold");
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	init_texture_menu(&data, scene->planes, scene->vols);
	handle_hooks(&data);
	mlx_loop(data.mlx_ptr);
	leave_rt(scene);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
