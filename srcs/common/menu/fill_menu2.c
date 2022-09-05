/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_menu2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:49:24 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 21:40:39 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "menu.h"
#include "mlx_data.h"
#include "utils.h"

#define WP WHITE_PIXEL
#define FX FOFFSET_MID_X

void	fill_field(t_data *data, int y, void *item, int type)
{
	char	str[50];

	if (type == m_int)
	{
		ft_itoa_custom(*((int *)item), &str[0], 50);
		mlx_string_put(data->mlx_ptr, data->win_ptr, FX, y, WP, &str[0]);
	}
	else if (type == m_float)
	{
		ft_ftoa_custom(*((float *)item), &str[0], 50);
		mlx_string_put(data->mlx_ptr, data->win_ptr, FX, y, WP, &str[0]);
	}
	else if (type == m_t_rgb)
	{
		fill_field(data, y, &((t_rgb *)item)->r, m_int);
		fill_field(data, y + STEP_FIELD, &((t_rgb *)item)->g, m_int);
		fill_field(data, y + STEP_FIELD * 2, &((t_rgb *)item)->b, m_int);
	}
	else if (type == m_t_pos)
	{
		fill_field(data, y, &((t_pos *)item)->x, m_float);
		fill_field(data, y + STEP_FIELD, &((t_pos *)item)->y, m_float);
		fill_field(data, y + STEP_FIELD * 2, &((t_pos *)item)->z, m_float);
	}
}

void	fill_camera(t_data *data, t_cam *cam, int y_start)
{
	y_start = RECT_START_Y + STEP_FIELD - FOFFSET_Y;
	y_start = fill_template(data, y_start, "CAMERA", 0);
	fill_field(data, y_start + STEP_FIELD, &cam->pos, m_t_pos);
	y_start = fill_template(data, y_start, "position", 1);
	fill_field(data, y_start + STEP_FIELD, &cam->vec3, m_t_pos);
	y_start = fill_template(data, y_start, "direction", 1);
	y_start += STEP_FIELD;
	fill_field(data, y_start, &cam->h_fov, m_int);
	y_start = fill_template(data, y_start, "fov", 3);
}

void	fill_ambient(t_data *data, t_list *lg, int y_start)
{
	t_light	*ambient;

	ambient = (t_light *)lg->content;
	y_start = fill_template(data, y_start, "AMBIENT LIGHT", 0);
	fill_field(data, y_start, &ambient->r, m_float);
	y_start = fill_template(data, y_start, "r", 3);
	fill_field(data, y_start + STEP_FIELD, &ambient->col, m_t_rgb);
	y_start = fill_template(data, y_start, "color", 2);
}

void	fill_light(t_data *data, t_list *lg, int y_start)
{
	t_light	*light;

	light = (t_light *)lg->content;
	y_start = fill_template(data, y_start, "LIGHT", 0);
	fill_field(data, y_start + STEP_FIELD, &light->pos, m_t_pos);
	y_start = fill_template(data, y_start, "position", 1);
	y_start += STEP_FIELD;
	fill_field(data, y_start, &light->r, m_float);
	y_start = fill_template(data, y_start, "r", 3);
	fill_field(data, y_start + STEP_FIELD, &light->col, m_t_rgb);
	y_start = fill_template(data, y_start, "color", 2);
}

void	fill_vol(t_data *data, t_list *lvol, int y_start)
{
	t_vol	*vol;

	vol = (t_vol *)lvol->content;
	if (vol->type == SPHERE)
	{
		y_start = fill_template(data, y_start, "SPHERE", 0);
		fill_field(data, y_start + STEP_FIELD, &vol->pos, m_t_pos);
		y_start = fill_template(data, y_start, "position", 1);
		y_start += STEP_FIELD;
	}
	if (vol->type == CYLINDER)
	{
		y_start = fill_template(data, y_start, "CYLINDER", 0);
		fill_field(data, y_start + STEP_FIELD, &vol->pos, m_t_pos);
		y_start = fill_template(data, y_start, "position", 1);
		fill_field(data, y_start + STEP_FIELD, &vol->vec3, m_t_pos);
		y_start = fill_template(data, y_start, "direction", 1);
		y_start += STEP_FIELD;
		fill_field(data, y_start, &vol->h, m_float);
		y_start = fill_template(data, y_start, "h", 3);
	}
	fill_field(data, y_start, &vol->d, m_float);
	y_start = fill_template(data, y_start, "d", 3);
	fill_field(data, y_start + STEP_FIELD, &vol->col, m_t_rgb);
	y_start = fill_template(data, y_start, "color", 2);
}
