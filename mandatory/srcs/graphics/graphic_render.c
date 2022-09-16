/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 18:05:22 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "utils.h"
#include "minirt.h"

int	get_color(t_rgb color)
{
	int	result;

	result = 0;
	result += color.r << 16;
	result += color.g << 8;
	result += color.b;
	return (result);
}

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
	t_rgb		color;
	int			xy_r_bar[4];

	xy_r_bar[0] = 0;
	xy_r_bar[1] = WIN_HEIGHT - 1;
	xy_r_bar[3] = xy_r_bar[1];
	xy_r_bar[2] = 0;
	ft_printf("\33[H\33[2J\33[3J");
	while (--xy_r_bar[1] >= 0)
	{
		xy_r_bar[2]++;
		ft_printf("\rRendering ... [ \x1b[1;32m%i%%\x1b[0m ]",
			(xy_r_bar[2] * 100) / xy_r_bar[3]);
		xy_r_bar[0] = 0;
		while (xy_r_bar[0]++ < WIN_WIDTH)
		{
			color = ray_render(xy_r_bar[1], xy_r_bar[0],
					data->scene->cam, data->scene);
			img_pix_put(&data->img, xy_r_bar[0], xy_r_bar[1], get_color(color));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	ft_printf("\n");
	return (0);
}
