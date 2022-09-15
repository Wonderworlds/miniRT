/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:45:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 23:30:33 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include "minirt.h"

void	str_vol(t_scene *scene, t_menu *menu)
{
	void	(*f[8])(t_menu *);
	int		add;
	int		type;

	f[0] = &bp_cam;
	f[1] = &bp_ambient;
	f[2] = &bp_light;
	f[3] = &bp_plane;
	f[4] = &bp_sphere;
	f[5] = &bp_cylinder;
	f[6] = &bp_triangle;
	f[7] = &bp_cylinder;
	if (menu->item == m_vol)
		type = ((t_vol *)ft_lst_at(scene->vols, menu->index)->content)->type;
	add = 0;
	if (type == CYLINDER)
		add = 1;
	if (type == TRIANGLE)
		add = 2;
	if (type == CONE)
		add = 3;
	(*f[menu->item + add])(menu);
}

static int	check_empty(t_scene *scene, int type)
{
	if (type == m_vol && !scene->vols)
		return (1);
	if (type == m_plane && !scene->planes)
		return (1);
	if (type == m_ambient && !scene->ambient)
		return (1);
	if (type == m_light && !scene->lights)
		return (1);
	return (0);
}

// void	graphic_refresh(t_data *data, t_delim x, t_delim y)
// {
// 	t_rgb		color;
// 	int			i;

// 	while (--y.max >= y.min)
// 	{
// 		i = x.min;
// 		while (i++ < x.max)
// 		{
// 			color = ray_render(y.max, i, data->scene->cam, data->scene);
// 			img_pix_put(&data->img, i, y.max, get_color(color));
// 		}
// 	}
// }

int	display_menu(t_data *data, t_menu *menu, t_scene *scene)
{
	size_t	size;

	if (check_empty(scene, menu->item))
	{
		menu->item++;
		if (menu->item > 4)
			menu->item = 0;
		display_menu(data, menu, scene);
	}
	str_vol(scene, menu);
	size = ft_strlen(&menu->bprint[0]);
	rect_display(data, gen_rect(RECT_START_X, RECT_END_X, RECT_START_Y,
			RECT_START_Y + FOFFSET_Y + (STEP_FIELD * size + 1)), BG_PIXEL);
	display_field(data, menu, size);
	select_field(data, menu, size);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	fill_menu(menu, data, scene);
	return (0);
}
