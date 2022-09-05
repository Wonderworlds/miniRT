/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:45:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 20:37:17 by fmauguin         ###   ########.fr       */
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
		x = rect.minX;
		while (x++ < rect.maxX)
		{
			img_pix_put(&data->img, x, rect.maxY, color);
		}
	}
}

t_rect	gen_rect(int minX, int maxX, int minY, int maxY)
{
	t_rect	ret;

	ret.maxX = maxX;
	ret.maxY = maxY;
	ret.minX = minX;
	ret.minY = minY;
	return (ret);
}

void	str_vol(t_scene *scene, t_menu *menu)
{
	if (menu->item == m_cam)
	{
		menu->bprint[0] = '0';
		menu->bprint[1] = '0';
		menu->bprint[2] = '1';
		menu->bprint[3] = '1';
		menu->bprint[4] = '1';
		menu->bprint[5] = '0';
		menu->bprint[6] = '1';
		menu->bprint[7] = '1';
		menu->bprint[8] = '1';
		menu->bprint[9] = '1';
		menu->bprint[10] = 0;
	}
	else if (menu->item == m_ambient)
	{
		menu->bprint[0] = '0';
		menu->bprint[1] = '1';
		menu->bprint[2] = '0';
		menu->bprint[3] = '1';
		menu->bprint[4] = '1';
		menu->bprint[5] = '1';
		menu->bprint[6] = 0;
	}
	else if (menu->item == m_light)
	{
		menu->bprint[0] = '1';
		menu->bprint[1] = '0';
		menu->bprint[2] = '1';
		menu->bprint[3] = '1';
		menu->bprint[4] = '1';
		menu->bprint[5] = '1';
		menu->bprint[6] = '0';
		menu->bprint[7] = '1';
		menu->bprint[8] = '1';
		menu->bprint[9] = '1';
		menu->bprint[11] = 0;
	}
	else if (menu->item == m_plane)
	{
		menu->bprint[0] = '1';
		menu->bprint[1] = '0';
		menu->bprint[2] = '1';
		menu->bprint[3] = '1';
		menu->bprint[4] = '1';
		menu->bprint[5] = '0';
		menu->bprint[6] = '1';
		menu->bprint[7] = '1';
		menu->bprint[8] = '1';
		menu->bprint[9] = '0';
		menu->bprint[10] = '1';
		menu->bprint[11] = '1';
		menu->bprint[12] = '1';
		menu->bprint[13] = 0;
	}
	else if (menu->item == m_vol &&((t_vol *)ft_lst_at(scene->vols,
		menu->index)->content)->type == SPHERE)
	{
		menu->bprint[0] = '1';
		menu->bprint[1] = '0';
		menu->bprint[2] = '1';
		menu->bprint[3] = '1';
		menu->bprint[4] = '1';
		menu->bprint[5] = '1';
		menu->bprint[6] = '0';
		menu->bprint[7] = '1';
		menu->bprint[8] = '1';
		menu->bprint[9] = '1';
		menu->bprint[10] = 0;
	}
	else if (menu->item == m_vol)
	{
		menu->bprint[0] = '1';
		menu->bprint[1] = '0';
		menu->bprint[2] = '1';
		menu->bprint[3] = '1';
		menu->bprint[4] = '1';
		menu->bprint[5] = '0';
		menu->bprint[6] = '1';
		menu->bprint[7] = '1';
		menu->bprint[8] = '1';
		menu->bprint[9] = '1';
		menu->bprint[10] = '1';
		menu->bprint[11] = '0';
		menu->bprint[12] = '1';
		menu->bprint[13] = '1';
		menu->bprint[14] = '1';
		menu->bprint[15] = 0;
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

void fill_field(t_data *data, int y, void *item, int type)
{
	char str[50];

	if (type == m_int)
	{
		ft_itoa_custom(*((int *)item), &str[0], 50);
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_MID_X, y, WHITE_PIXEL, &str[0]);
	}
	else if (type == m_float)
	{
		ft_ftoa_custom(*((float *)item), &str[0], 50);
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_MID_X, y, WHITE_PIXEL, &str[0]);
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

int	fill_template(t_data *data, int y_start, char *name,  const int type)
{
	if (type == 0)
		mlx_string_put(data->mlx_ptr, data->win_ptr,
			FOFFSET_TITLE_X, y_start, WHITE_PIXEL, name);
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
			FOFFSET_1_X - (FOFFSET_X / 2), y_start, WHITE_PIXEL, name);
	}
	return (y_start + STEP_FIELD);
}

void	fill_camera(t_data *data, t_cam *cam, int y_start)
{
	y_start = RECT_START_Y + STEP_FIELD - FOFFSET_Y;
	y_start = fill_template(data, y_start, "CAMERA", 0);
	fill_field(data, y_start + STEP_FIELD, &cam->pos, m_t_pos);
	y_start = fill_template(data, y_start, "position", 1);
	fill_field(data, y_start + STEP_FIELD, &cam->vec3, m_t_pos);
	y_start = fill_template(data, y_start, "direction", 1);
	fill_field(data, y_start, &cam->h_fov, m_int);
	y_start = fill_template(data, y_start, "fov", 3);
}

void	fill_ambient(t_data *data, t_list *lg, int y_start)
{
	t_light	*ambient;

	ambient = (t_light *)lg->content;
	y_start = fill_template(data, y_start, "AMBIENT LIGHT", 0);
	fill_field(data, y_start + STEP_FIELD, &ambient->r, m_float);
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
	fill_field(data, y_start + STEP_FIELD, &light->r, m_float);
	y_start = fill_template(data, y_start, "r", 3);
	fill_field(data, y_start + STEP_FIELD, &light->col, m_t_rgb);
	y_start = fill_template(data, y_start, "color", 2);
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

void	fill_vol(t_data *data, t_list *lvol, int y_start)
{
	t_vol	*vol;

	vol = (t_vol *)lvol->content;
	if (vol->type == SPHERE)
	{
		y_start = fill_template(data, y_start, "SPHERE", 0);
		fill_field(data, y_start + STEP_FIELD, &vol->pos, m_t_pos);
		y_start = fill_template(data, y_start, "position", 1);

	}
	if (vol->type == CYLINDER)
	{
		y_start = fill_template(data, y_start, "CYLINDER", 0);
		fill_field(data, y_start + STEP_FIELD, &vol->pos, m_t_pos);
		y_start = fill_template(data, y_start, "position", 1);
		fill_field(data, y_start + STEP_FIELD, &vol->vec3, m_t_pos);
		fill_field(data, y_start + STEP_FIELD, &vol->h, m_float);
		y_start = fill_template(data, y_start, "h", 3);
	}
	fill_field(data, y_start + STEP_FIELD, &vol->d, m_float);
	y_start = fill_template(data, y_start, "d", 3);
	fill_field(data, y_start + STEP_FIELD, &vol->col, m_t_rgb);
	y_start = fill_template(data, y_start, "color", 2);
}

void	fill_menu(t_menu *menu, t_data *data, t_scene *scene)
{
	int		y_start;

	y_start = RECT_START_Y + STEP_FIELD - FOFFSET_Y;
	if (menu->item == m_cam)
		fill_camera(data, &scene->cam, y_start);
	else if (menu->item == m_ambient)
		fill_ambient(data, scene->lights, y_start);
	else if (menu->item == m_light)
		fill_light(data, ft_lst_at(scene->lights, menu->index), y_start);
	else if (menu->item == m_plane)
		fill_plane(data, ft_lst_at(scene->planes, menu->index), y_start);
	else if (menu->item == m_vol)
		fill_vol(data, ft_lst_at(scene->vols, menu->index), y_start);
}


int	display_menu(t_data *data, t_menu *menu, t_scene *scene)
{
	size_t	size;

	menu->is_visible = true;
	menu->item = 0;
	str_vol(scene, menu);
	size = ft_strlen(&menu->bprint[0]);
	rect_display(data, gen_rect(RECT_START_X, RECT_END_X, RECT_START_Y,
		RECT_START_Y + FOFFSET_Y + (STEP_FIELD * size + 1)), BG_PIXEL);
	display_field(data, menu, size);
	select_field(data, menu, size);
	return (0);
}