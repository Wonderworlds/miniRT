/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/17 15:25:48 by amahla           ###   ########.fr       */
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

int	img_pix_put(t_img_c *img, t_couple pos, t_couple lim, int color)
{
	char	*pixel;

	if (pos.x < 0 || pos.y < 0 || pos.x >= lim.x || pos.y >= lim.y)
		return (0);
	pixel = img->addr + (pos.y * img->line_len + pos.x * (img->bpp / 8));
	*(int *)pixel = color;
	return (1);
}

void	graphic_render(t_data *data, t_couple lim)
{
	t_rgb		color;
	int			xy_r_bar[4];

	xy_r_bar[0] = 0;
	xy_r_bar[1] = lim.y - 1;
	xy_r_bar[3] = xy_r_bar[1];
	xy_r_bar[2] = 0;
	ft_printf("\33[H\33[2J\33[3J");
	while (--xy_r_bar[1] >= 0)
	{
		xy_r_bar[2]++;
		ft_printf("\rRendering ... [\x1b[1;32m %i%% \x1b[0m]",
			(xy_r_bar[2] * 100) / xy_r_bar[3]);
		xy_r_bar[0] = 0;
		while (xy_r_bar[0]++ < lim.x)
		{
			color = ray_render(xy_r_bar[1], xy_r_bar[0],
					data->scene->cam, data->scene);
			img_pix_put(&data->img, gen_couple(xy_r_bar[0], xy_r_bar[1]),
				gen_couple(lim.x, lim.y), get_color(color));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	ft_printf("\n");
}
