/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/08/22 16:52:01 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"

int	key_press_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
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
	mlx_loop_hook(data->mlx_ptr, &graphic_render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, key_press_hook, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		exit_hook, data);
}
