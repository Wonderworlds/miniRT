/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/17 23:12:33 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "libft.h"
#include "utils.h"

#define XK_ENTER 65293

int	exit_hook(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	key_press_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		if (data->menu.is_visible)
			close_menu(data);
		else
			return (exit_hook(data));
	}
	if (keysym == XK_ENTER && data->menu.is_visible)
		close_menu(data);
	if (keysym == XK_Tab)
		switch_menu(data);
	if (keysym == XK_Down && data->menu.is_visible)
		updown_menu(data, -1);
	if (keysym == XK_Up && data->menu.is_visible)
		updown_menu(data, 1);
	if (keysym == XK_Left && data->menu.is_visible)
		left_right_menu(data, -1);
	if (keysym == XK_Right && data->menu.is_visible)
		left_right_menu(data, 1);
	return (0);
}

void	handle_hooks(t_data *data)
{
	graphic_render(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press_hook, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		exit_hook, data);
}
