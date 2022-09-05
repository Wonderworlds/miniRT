/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dec_menu2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 23:57:22 by fmauguin         ###   ########.fr       */
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
		add_dec(&pl->pos.x, m_float, i);
	else if (menu->field_index == 2)
		add_dec(&pl->pos.y, m_float, i);
	else if (menu->field_index == 3)
		add_dec(&pl->pos.z, m_float, i);
	else if (menu->field_index == 4)
		add_dec(&pl->vec3.x, m_float, i);
	else if (menu->field_index == 5)
		add_dec(&pl->vec3.y, m_float, i);
	else if (menu->field_index == 6)
		add_dec(&pl->vec3.z, m_float, i);
	else if (menu->field_index == 7)
		add_dec(&pl->col.r, m_int, i);
	else if (menu->field_index == 8)
		add_dec(&pl->col.g, m_int, i);
	else if (menu->field_index == 9)
		add_dec(&pl->col.b, m_int, i);
	return (0);
}

int	add_dec_sphere(t_data *data, int i)
{
	t_menu	*menu;
	t_vol	*sp;

	menu = &data->menu;
	if (menu->field_index == 0)
		return (check_lst_index(data->scene->vols, &menu->index, i));
	sp = (t_vol *)(ft_lst_at(data->scene->vols,
				menu->index)->content);
	if (menu->field_index == 1)
		add_dec(&sp->pos.x, m_float, i);
	else if (menu->field_index == 2)
		add_dec(&sp->pos.y, m_float, i);
	else if (menu->field_index == 3)
		add_dec(&sp->pos.z, m_float, i);
	else if (menu->field_index == 4)
		add_dec(&sp->d, m_float, i);
	else if (menu->field_index == 5)
		add_dec(&sp->col.r, m_int, i);
	else if (menu->field_index == 6)
		add_dec(&sp->col.g, m_int, i);
	else if (menu->field_index == 7)
		add_dec(&sp->col.b, m_int, i);
	return (0);
}

void	add_dec_cylinder2(int i, t_menu *menu, t_vol *cy)
{
	if (menu->field_index == 4)
		add_dec(&cy->vec3.x, m_float, i);
	else if (menu->field_index == 5)
		add_dec(&cy->vec3.y, m_float, i);
	else if (menu->field_index == 6)
		add_dec(&cy->vec3.z, m_float, i);
	else if (menu->field_index == 7)
		add_dec(&cy->h, m_float, i);
	else if (menu->field_index == 8)
		add_dec(&cy->d, m_float, i);
	else if (menu->field_index == 9)
		add_dec(&cy->col.r, m_int, i);
	else if (menu->field_index == 10)
		add_dec(&cy->col.g, m_int, i);
	else if (menu->field_index == 11)
		add_dec(&cy->col.b, m_int, i);
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
		add_dec(&cy->pos.x, m_float, i);
	else if (menu->field_index == 2)
		add_dec(&cy->pos.y, m_float, i);
	else if (menu->field_index == 3)
		add_dec(&cy->pos.z, m_float, i);
	else
		add_dec_cylinder2(i, menu, cy);
	return (0);
}
