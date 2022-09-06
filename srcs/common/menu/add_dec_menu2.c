/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dec_menu2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/06 16:01:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"

int	check_lst_index(t_list *lst, int *index, int i)
{
	int	size;

	size = ft_lstsize(lst);
	if (size == 1)
	{
		ft_fprintf(2, "Error\nOnly one item in this list\n");
		return (1);
	}
	*index += i;
	if (*index >= size)
		*index = 0;
	if (*index < 0)
		*index = size - 1;
	return (0);
}

static void	add_dec_plane2(t_plane *pl, int i, t_menu *menu)
{
	if (menu->field_index == 4)
		add_dec_float(&pl->vec3.x, i, gen_lim(-1, 1));
	else if (menu->field_index == 5)
		add_dec_float(&pl->vec3.y, i, gen_lim(-1, 1));
	else if (menu->field_index == 6)
		add_dec_float(&pl->vec3.z, i, gen_lim(-1, 1));
	else if (menu->field_index == 7)
		add_dec_int(&pl->col.r, i, gen_lim(0, 255));
	else if (menu->field_index == 8)
		add_dec_int(&pl->col.g, i, gen_lim(0, 255));
	else if (menu->field_index == 9)
		add_dec_int(&pl->col.b, i, gen_lim(0, 255));
}

int	add_dec_plane(t_data *data, int i)
{
	t_menu	*menu;
	t_plane	*pl;

	menu = &data->menu;
	if (menu->field_index == 0)
		return (check_lst_index(data->scene->planes, &menu->index, i));
	pl = (t_plane *)(ft_lst_at(data->scene->planes,
				menu->index)->content);
	if (menu->field_index == 1)
		add_dec_float(&pl->pos.x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 2)
		add_dec_float(&pl->pos.y, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 3)
		add_dec_float(&pl->pos.z, i, gen_lim(-10000, 10000));
	else
		add_dec_plane2(pl, i, menu);
	return (0);
}

static void	add_dec_cylinder2(int i, t_menu *menu, t_vol *cy)
{
	if (menu->field_index == 4)
		add_dec_float(&cy->vec3.x, i, gen_lim(-1, 1));
	else if (menu->field_index == 5)
		add_dec_float(&cy->vec3.y, i, gen_lim(-1, 1));
	else if (menu->field_index == 6)
		add_dec_float(&cy->vec3.z, i, gen_lim(-1, 1));
	else if (menu->field_index == 7)
		add_dec_float(&cy->h, i, gen_lim(0, 10000));
	else if (menu->field_index == 8)
		add_dec_float(&cy->d, i, gen_lim(0, 10000));
	else if (menu->field_index == 9)
		add_dec_int(&cy->col.r, i, gen_lim(0, 255));
	else if (menu->field_index == 10)
		add_dec_int(&cy->col.g, i, gen_lim(0, 255));
	else if (menu->field_index == 11)
		add_dec_int(&cy->col.b, i, gen_lim(0, 255));
}

int	add_dec_cylinder(t_data *data, int i)
{
	t_menu	*menu;
	t_vol	*cy;

	menu = &data->menu;
	if (menu->field_index == 0)
		return (check_lst_index(data->scene->vols, &menu->index, i));
	cy = (t_vol *)(ft_lst_at(data->scene->vols,
				menu->index)->content);
	if (menu->field_index == 1)
		add_dec_float(&cy->pos.x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 2)
		add_dec_float(&cy->pos.y, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 3)
		add_dec_float(&cy->pos.z, i, gen_lim(-10000, 10000));
	else
		add_dec_cylinder2(i, menu, cy);
	return (0);
}
