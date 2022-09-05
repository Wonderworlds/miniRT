/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:45:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 22:01:18 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include "minirt.h"

void	bp_cam(t_menu *menu)
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
	menu->bprint[9] = '0';
	menu->bprint[10] = '1';
	menu->bprint[11] = 0;
	menu->max_f_index = 6;
}

void	str_vol(t_scene *scene, t_menu *menu)
{
	void	(*f[6])(t_menu *);
	int		add;

	f[0] = &bp_cam;
	f[1] = &bp_ambient;
	f[2] = &bp_light;
	f[3] = &bp_plane;
	f[4] = &bp_sphere;
	f[5] = &bp_cylinder;
	add = 0;
	if (menu->item == m_vol && ((t_vol *)ft_lst_at(scene->vols,
				menu->index)->content)->type == CYLINDER)
		add = 1;
	(*f[menu->item + add])(menu);
}

int	display_menu(t_data *data, t_menu *menu, t_scene *scene)
{
	size_t	size;

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
