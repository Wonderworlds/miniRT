/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/08 15:47:14 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"
#include "minirt.h"
#include "bvh.h"

void	close_menu(t_data *data)
{
	int	size;

	data->menu.is_visible = false;
	update_unit_vector(data->menu.item, data->scene);
	if (data->menu.has_changed)
	{
		size = ft_lstsize(data->scene->vols) - 1;
		if (size >= 0)
		{
			btree_remove_infix(&data->scene->bvh, &free);
			update_bounds_vol(data->scene->vols);
			build_node(&data->scene->vols, &data->scene->bvh, 0,
				(unsigned int)size);
		}
	}
	graphic_render(data);
}

void	open_menu(t_data *data)
{
	data->menu.is_visible = true;
	data->menu.has_changed = false;
	set_save_img(&data->img,
		gen_rect(RECT_START_X, RECT_END_X, RECT_START_Y2, RECT_END_Y2));
	display_menu(data, &data->menu, data->scene);
}

void	switch_menu(t_data *data)
{
	data->menu.field_index = 0;
	if (data->menu.is_visible)
	{
		update_unit_vector(data->menu.item, data->scene);
		data->menu.index = 0;
		data->menu.item++;
		if (data->menu.item > 4)
			data->menu.item = 0;
		get_save_img(&data->img,
			gen_rect(RECT_START_X, RECT_END_X, RECT_START_Y2, RECT_END_Y2));
		display_menu(data, &data->menu, data->scene);
	}
	else
		open_menu(data);
}

void	updown_menu(t_data *data, int i)
{
	if (i == -1)
	{
		data->menu.field_index++;
		if (data->menu.field_index > data->menu.max_f_index)
			data->menu.field_index = 0;
	}
	else
	{
		data->menu.field_index--;
		if (data->menu.field_index < 0)
			data->menu.field_index = data->menu.max_f_index;
	}
	display_menu(data, &data->menu, data->scene);
}

void	left_right_menu(t_data *data, int i)
{
	int		(*f[6])(t_data *, int );
	int		add;
	t_menu	*menu;

	menu = &data->menu;
	f[0] = &add_dec_cam;
	f[1] = &add_dec_ambient;
	f[2] = &add_dec_light;
	f[3] = &add_dec_plane;
	f[4] = &add_dec_sphere;
	f[5] = &add_dec_cylinder;
	add = 0;
	if (menu->item == m_vol && ((t_vol *)ft_lst_at(data->scene->vols,
				menu->index)->content)->type == CYLINDER)
		add = 1;
	if (!(*f[menu->item + add])(data, i))
		display_menu(data, &data->menu, data->scene);
}
