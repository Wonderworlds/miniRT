/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:45:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 13:51:54 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include "minirt.h"


void	rect_display(t_data *data, t_rect rect, int color)
{
	int	x;

	while (--rect.maxY >= rect.minY)
	{
		x = rect.minY;
		while (x++ < rect.maxX)
		{
			img_pix_put(&data->img, x, rect.maxY, color);
		}
	}
}

t_rect	gen_rect(int minX, int minY, int maxX, int maxY)
{
	t_rect	ret;

	ret.maxX = maxX;
	ret.maxY = maxY;
	ret.minX = minX;
	ret.minY = minY;
	return (ret);
}

int	display_menu(t_data *data, t_scene *scene)
{
	(void)scene;
	rect_display(data, gen_rect(RECT_START_X, RECT_START_Y, 200, 500),
		BG_PIXEL);
	rect_display(data, gen_rect(RECT_START_X + 10, RECT_START_Y + 20, 180, 100),
		BGFIELD_PIXEL);
	return (0);
}