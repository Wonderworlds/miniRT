/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/06 16:23:06 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "utils.h"
#include "minirt.h"

int get_color(t_rgb color)
{
  int              result;

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
	int			y;
	int			x;
	t_rgb		color;
	int			r_bar[2];

	x = 0;
	y = WIN_HEIGHT - 1;
	r_bar[1] = y;
	r_bar[0] = 0;
	if (!data->win_ptr)
		return (1);
	while (--y >= 0)
	{
		r_bar[0]++;
		ft_printf("\rRendering ... [ \x1b[1;32m%i%%\x1b[0m ]",
			(r_bar[0] * 100) / r_bar[1]);
		x = 0;
		while (x++ < WIN_WIDTH)
		{
			color = ray_render(y, x, data->scene->cam, data->scene);
			img_pix_put(&data->img, x, y, get_color(color));
		}
	}
	ft_printf("\n");
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}
