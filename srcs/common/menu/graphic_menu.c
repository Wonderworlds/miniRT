/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:45:43 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 21:19:04 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include "minirt.h"

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
		menu->bprint[9] = '0';
		menu->bprint[10] = '1';
		menu->bprint[11] = 0;
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
		menu->bprint[5] = '0';
		menu->bprint[6] = '1';
		menu->bprint[7] = '0';
		menu->bprint[8] = '1';
		menu->bprint[9] = '1';
		menu->bprint[10] = '1';
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
		menu->bprint[5] = '0';
		menu->bprint[6] = '1';
		menu->bprint[7] = '0';
		menu->bprint[8] = '1';
		menu->bprint[9] = '1';
		menu->bprint[10] = '1';
		menu->bprint[11] = 0;
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
		menu->bprint[9] = '0';
		menu->bprint[10] = '1';
		menu->bprint[11] = '1';
		menu->bprint[12] = '0';
		menu->bprint[13] = '1';
		menu->bprint[14] = '1';
		menu->bprint[15] = '1';
		menu->bprint[16] = 0;
	}
}

int	display_menu(t_data *data, t_menu *menu, t_scene *scene)
{
	size_t	size;

	menu->is_visible = true;
	menu->item = 4;
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