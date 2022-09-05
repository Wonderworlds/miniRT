/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:16:34 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 21:37:00 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "structs_utils.h"
#include "mlx_data.h"

t_rect	gen_rect(int minX, int maxX, int minY, int maxY)
{
	t_rect	ret;

	ret.maxX = maxX;
	ret.maxY = maxY;
	ret.minX = minX;
	ret.minY = minY;
	return (ret);
}

void	rect_display(t_data *data, t_rect rect, int color)
{
	int	x;

	while (--rect.maxY >= rect.minY)
	{
		x = rect.minX;
		while (x++ < rect.maxX)
		{
			img_pix_put(&data->img, x, rect.maxY, color);
		}
	}
}

void	display_field(t_data *data, t_menu *menu, size_t size)
{
	size_t	i;
	int		y_start;
	int		x_start;

	i = 0;
	while (i < size)
	{
		if (menu->bprint[i] == '1')
		{
			x_start = RECT_START_X + FOFFSET_X;
			y_start = RECT_START_Y + FOFFSET_Y;
			if (i != 0)
			{
				y_start += STEP_FIELD * i;
				x_start += FOFFSET_X * 3;
			}
			rect_display(data,
				gen_rect(x_start, RECT_END_X - FOFFSET_X,
					y_start, y_start + STEP_FIELD - FOFFSET_Y),
				BGFIELD_PIXEL);
		}
		i++;
	}
}

void	select_field(t_data *data, t_menu *menu, size_t size)
{
	size_t	i;
	int		y_start;
	int		x_start;
	int		f_index;

	i = -1;
	f_index = menu->field_index + 1;
	while (++i < size && f_index)
		if (menu->bprint[i] == '1' && --f_index == 0)
			break ;
	if (i != size)
	{
		x_start = FOFFSET_1_X;
		y_start = RECT_START_Y + FOFFSET_Y;
		if (i != 0)
		{
			y_start += STEP_FIELD * i;
			x_start = FOFFSET_TITLE_X;
		}
		rect_display(data,
			gen_rect(x_start, RECT_END_X - FOFFSET_X,
				y_start, y_start + STEP_FIELD - FOFFSET_Y),
			SELFIELD_PIXEL);
	}
}
