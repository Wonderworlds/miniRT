/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 22:25:54 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"

void	close_menu(t_data *data)
{
	data->menu.is_visible = false;
	graphic_render(data);
}

void	open_menu(t_data *data)
{
	data->menu.is_visible = true;
	data->menu.field_index = 0;
	display_menu(data, &data->menu, data->scene);
}

void	switch_menu(t_data *data)
{
	if (data->menu.is_visible)
	{
		data->menu.item++;
		if (data->menu.item > 4)
			data->menu.item = 0;
	}
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