/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/06 18:04:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"

void	close_menu(t_data *data)
{
	data->menu.is_visible = false;
	graphic_render(data);
}

void	open_menu(t_data *data)
{
	display_menu(data, &data->menu, data->scene);
}

void	switch_menu(t_data *data)
{
	data->menu.field_index = 0;
	if (data->menu.is_visible)
	{
		data->menu.index = 0;
		data->menu.item++;
		if (data->menu.item > 4)
			data->menu.item = 0;
		graphic_refresh(data, gen_lim(RECT_START_X, RECT_END_X),
			gen_lim(RECT_START_Y, RECT_START_Y + STEP_FIELD * 16));
	}
	else
		data->menu.is_visible = true;
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
