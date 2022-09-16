/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:46:58 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 20:17:38 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "menu.h"
#include "mlx_data.h"

static int	fill_template2(t_data *data, int y_start, char *name,
				const int type)
{
	if (type == 0)
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_TITLE_X + FOFFSET_1_X, y_start, WHITE_PIXEL, name);
	else if (type == 1)
	{
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_TITLE_X, y_start, WHITE_PIXEL, name);
		y_start += STEP_FIELD;
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_1_X, y_start, WHITE_PIXEL, "x");
		y_start += STEP_FIELD;
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_1_X, y_start, WHITE_PIXEL, "y");
		y_start += STEP_FIELD;
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_1_X, y_start, WHITE_PIXEL, "z");
	}
	return (y_start + STEP_FIELD);
}

int	fill_template(t_data *data, int y_start, char *name, const int type)
{
	if (type < 2)
		return (fill_template2(data, y_start, name, type));
	else if (type == 2)
	{
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_TITLE_X, y_start, WHITE_PIXEL, name);
		y_start += STEP_FIELD;
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_1_X, y_start, WHITE_PIXEL, "r");
		y_start += STEP_FIELD;
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_1_X, y_start, WHITE_PIXEL, "g");
		y_start += STEP_FIELD;
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_1_X, y_start, WHITE_PIXEL, "b");
	}
	else if (type == 3)
	{
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_1_X, y_start, WHITE_PIXEL, name);
	}
	return (y_start + STEP_FIELD);
}

void	fill_plane(t_data *data, t_list *lpl, int y_start)
{
	t_plane	*pl;

	pl = (t_plane *)lpl->content;
	y_start = fill_template(data, y_start, "PLANE", 0);
	fill_field(data, y_start + STEP_FIELD, &pl->pos, m_t_pos);
	y_start = fill_template(data, y_start, "position", 1);
	fill_field(data, y_start + STEP_FIELD, &pl->vec3, m_t_pos);
	y_start = fill_template(data, y_start, "direction", 1);
	fill_field(data, y_start + STEP_FIELD, &pl->col, m_t_rgb);
	y_start = fill_template(data, y_start, "color", 2);
}

void	fill_ambient(t_data *data, t_light *lg, int y_start)
{
	y_start = fill_template(data, y_start, "AMBIENT LIGHT", 0);
	fill_field(data, y_start, &lg->r_o, m_float);
	y_start = fill_template(data, y_start, "r", 3);
	fill_field(data, y_start + STEP_FIELD, &lg->col, m_t_rgb);
	y_start = fill_template(data, y_start, "color", 2);
}
