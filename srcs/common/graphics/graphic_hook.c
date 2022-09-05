/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/05 22:09:38 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "libft.h"

#define XK_Enter 65293

int	key_press_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		if (data->menu.is_visible)
		{
			data->menu.is_visible = false;
			graphic_render(data);
		}
		else
		{
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			data->win_ptr = NULL;
			mlx_loop_end(data->mlx_ptr);
		}
	}
	if (keysym == XK_Enter)
	{
		if (data->menu.is_visible)
		{
			data->menu.is_visible = false;
			graphic_render(data);
		}
	}
	if (keysym == XK_Tab)
	{
		if (data->menu.is_visible)
		{
			data->menu.item++;
			if (data->menu.item > 4)
				data->menu.item = 0;
		}
		data->menu.is_visible = true;
		data->menu.field_index = 0;
		display_menu(data, &data->menu, data->scene);
	}
	if (keysym == XK_Down)
	{
		if (data->menu.is_visible)
		{
			data->menu.field_index++;
			if (data->menu.field_index > data->menu.max_f_index)
				data->menu.field_index = 0;
			display_menu(data, &data->menu, data->scene);
		}
	}
	if (keysym == XK_Up)
	{
		if (data->menu.is_visible)
		{
			data->menu.field_index--;
			if (data->menu.field_index < 0)
				data->menu.field_index = data->menu.max_f_index;
			display_menu(data, &data->menu, data->scene);
		}
	}
	return (0);
}

int	exit_hook(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

void	handle_hooks(t_data *data)
{
	graphic_render(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press_hook, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		exit_hook, data);
}
