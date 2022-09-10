/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/10 17:25:12 by fmauguin         ###   ########.fr       */
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

int	img_pix_put(t_img *img, t_couple pos, t_couple lim, int color)
{
	char	*pixel;

	if (pos.x < 0 || pos.y < 0 || pos.x >= lim.x || pos.y >= lim.y)
		return (0);
	pixel = img->addr + (pos.y * img->line_len + pos.x * (img->bpp / 8));
	*(int *)pixel = color;
	return (1);
}

int	graphic_render(t_data *data, t_couple lim)
{
	int			y;
	int			x;
	t_rgb		color;
	int			r_bar[2];

	x = 0;
	y = lim.y - 1;
	r_bar[1] = y;
	r_bar[0] = 0;
	while (--y >= 0)
	{
		r_bar[0]++;
		ft_printf("\rRendering ... [ \x1b[1;32m%i%%\x1b[0m ]",
			(r_bar[0] * 100) / r_bar[1]);
		x = 0;
		while (x++ < lim.x)
		{
			color = ray_render(y, x, data->scene->cam, data->scene);
			img_pix_put(&data->img, gen_couple(x, y),
				gen_couple(lim.x, lim.y), get_color(color));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}
