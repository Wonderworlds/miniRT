/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dec_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 23:58:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"

void	add_dec(void *value, int type, int op)
{
	float	*f;
	int		*i;

	f = (float *)value;
	i = (int *)value;
	if (op == 1)
	{
		if (type == m_float)
			*f += 0.1f;
		else
			*i += 1;
	}
	else
	{
		if (type == m_float)
			*f -= 0.1f;
		else
			*i -= 1;
	}
}

int	add_dec_cam(t_data *data, int i)
{
	t_menu	*menu;

	menu = &data->menu;
	if (menu->field_index == 0)
		add_dec(&data->scene->cam.pos.x, m_float, i);
	else if (menu->field_index == 1)
		add_dec(&data->scene->cam.pos.y, m_float, i);
	else if (menu->field_index == 2)
		add_dec(&data->scene->cam.pos.z, m_float, i);
	else if (menu->field_index == 3)
		add_dec(&data->scene->cam.vec3.x, m_float, i);
	else if (menu->field_index == 4)
		add_dec(&data->scene->cam.vec3.y, m_float, i);
	else if (menu->field_index == 5)
		add_dec(&data->scene->cam.vec3.z, m_float, i);
	else if (menu->field_index == 6)
	{
		add_dec(&data->scene->cam.h_fov, m_int, i);
		set_camera(&data->scene->cam);
	}
	return (0);
}

int	add_dec_ambient(t_data *data, int i)
{
	t_menu	*menu;
	t_light	*ambient;

	menu = &data->menu;
	ambient = (t_light *)data->scene->lights->content;
	if (menu->field_index == 0)
		add_dec(&ambient->r, m_float, i);
	else if (menu->field_index == 1)
		add_dec(&ambient->col.r, m_int, i);
	else if (menu->field_index == 2)
		add_dec(&ambient->col.g, m_int, i);
	else if (menu->field_index == 3)
		add_dec(&ambient->col.b, m_int, i);
	return (0);
}

int	add_dec_light(t_data *data, int i)
{
	t_menu	*menu;
	t_light	*light;

	menu = &data->menu;
	if (menu->field_index == 0)
		return (check_lst_index(data->scene->lights->next, &menu->index, i));
	light = (t_light *)(ft_lst_at(data->scene->lights->next,
				menu->index)->content);
	if (menu->field_index == 1)
		add_dec(&light->pos.x, m_float, i);
	else if (menu->field_index == 2)
		add_dec(&light->pos.y, m_float, i);
	else if (menu->field_index == 3)
		add_dec(&light->pos.z, m_float, i);
	else if (menu->field_index == 4)
		add_dec(&light->r, m_float, i);
	else if (menu->field_index == 5)
		add_dec(&light->col.r, m_int, i);
	else if (menu->field_index == 6)
		add_dec(&light->col.g, m_int, i);
	else if (menu->field_index == 7)
		add_dec(&light->col.b, m_int, i);
	return (0);
}
