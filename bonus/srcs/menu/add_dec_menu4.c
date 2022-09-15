/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dec_menu4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 23:35:30 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"

static void	add_dec_triangle2(int i, t_menu *menu, t_vol *co)
{
	if (menu->field_index == 4)
		add_dec_float(&co->tr[1].x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 5)
		add_dec_float(&co->tr[1].y, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 6)
		add_dec_float(&co->tr[1].z, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 7)
		add_dec_float(&co->tr[2].x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 8)
		add_dec_float(&co->tr[2].x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 9)
		add_dec_float(&co->tr[2].x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 10)
		add_dec_float(&co->h, i, gen_lim(0, 10000));
	else if (menu->field_index == 11)
		add_dec_float(&co->d, i, gen_lim(0, 10000));
	else if (menu->field_index == 12)
		add_dec_int(&co->col.r, i, gen_lim(0, 255));
	else if (menu->field_index == 13)
		add_dec_int(&co->col.g, i, gen_lim(0, 255));
	else if (menu->field_index == 14)
		add_dec_int(&co->col.b, i, gen_lim(0, 255));
}

int	add_dec_triangle(t_data *data, int i)
{
	t_menu	*menu;
	t_vol	*co;

	menu = &data->menu;
	if (menu->field_index == 0)
	{
		if (check_lst_index(data->scene->vols, &menu->index, i))
			return (1);
		get_save_img(&data->img,
			gen_rect(RECT_START_X, RECT_END_X, RECT_START_Y2, RECT_END_Y2));
		return (0);
	}
	co = (t_vol *)(ft_lst_at(data->scene->vols,
				menu->index)->content);
	if (menu->field_index == 1)
		add_dec_float(&co->tr[0].x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 2)
		add_dec_float(&co->tr[0].y, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 3)
		add_dec_float(&co->tr[0].z, i, gen_lim(-10000, 10000));
	else
		add_dec_triangle2(i, menu, co);
	if (1 <= menu->field_index && menu->field_index <= 11)
		menu->has_changed = true;
	return (0);
}
