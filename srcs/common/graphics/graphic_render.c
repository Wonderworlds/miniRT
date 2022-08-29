/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/08/22 16:53:06 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"mlx_data.h"

int	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return (0);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
	return (1);
}

int	graphic_render(t_data *data)
{
	if (!data->win_ptr)
		return (1);
/*	while (1)
	{
		 Raytracing ...
		  
		img_pix_put(data->img, x, y, color);
		
	}*/
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}
