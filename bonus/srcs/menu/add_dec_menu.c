/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dec_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:59:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"

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
		add_dec_double(&sp->pos.x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 2)
		add_dec_double(&sp->pos.y, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 3)
		add_dec_double(&sp->pos.z, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 4)
		add_dec_double(&sp->d, i, gen_lim(0, 10000));
	else if (menu->field_index == 5)
		add_dec_int(&sp->col.r, i, gen_lim(0, 255));
	else if (menu->field_index == 6)
		add_dec_int(&sp->col.g, i, gen_lim(0, 255));
	else if (menu->field_index == 7)
		add_dec_int(&sp->col.b, i, gen_lim(0, 255));
	if (1 <= menu->field_index && menu->field_index <= 4)
		menu->has_changed = true;
	return (0);
}

int	add_dec_cam(t_data *data, int i)
{
	t_menu	*menu;

	menu = &data->menu;
	if (menu->field_index == 0)
		add_dec_double(&data->scene->cam->pos.x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 1)
		add_dec_double(&data->scene->cam->pos.y, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 2)
		add_dec_double(&data->scene->cam->pos.z, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 3)
		add_dec_double(&data->scene->cam->vec3.x, i, gen_lim(-1, 1));
	else if (menu->field_index == 4)
		add_dec_double(&data->scene->cam->vec3.y, i, gen_lim(-1, 1));
	else if (menu->field_index == 5)
		add_dec_double(&data->scene->cam->vec3.z, i, gen_lim(-1, 1));
	else if (menu->field_index == 6)
		add_dec_int(&data->scene->cam->h_fov, i, gen_lim(0, 180));
	set_camera(data->scene->cam, &data->scene->resolut);
	return (0);
}

int	add_dec_ambient(t_data *data, int i)
{
	t_menu	*menu;
	t_light	*ambient;

	menu = &data->menu;
	ambient = data->scene->ambient;
	if (menu->field_index == 0)
		add_dec_double(&ambient->r, i, gen_lim(0, 1));
	else if (menu->field_index == 1)
		add_dec_int(&ambient->col.r, i, gen_lim(0, 255));
	else if (menu->field_index == 2)
		add_dec_int(&ambient->col.g, i, gen_lim(0, 255));
	else if (menu->field_index == 3)
		add_dec_int(&ambient->col.b, i, gen_lim(0, 255));
	return (0);
}

int	add_dec_light(t_data *data, int i)
{
	t_menu	*menu;
	t_light	*light;

	menu = &data->menu;
	if (menu->field_index == 0)
		return (check_lst_index(data->scene->lights, &menu->index, i));
	light = (t_light *)(ft_lst_at(data->scene->lights,
				menu->index)->content);
	if (menu->field_index == 1)
		add_dec_double(&light->pos.x, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 2)
		add_dec_double(&light->pos.y, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 3)
		add_dec_double(&light->pos.z, i, gen_lim(-10000, 10000));
	else if (menu->field_index == 4)
		add_dec_double(&light->r, i, gen_lim(0, 1));
	else if (menu->field_index == 5)
		add_dec_int(&light->col.r, i, gen_lim(0, 255));
	else if (menu->field_index == 6)
		add_dec_int(&light->col.g, i, gen_lim(0, 255));
	else if (menu->field_index == 7)
		add_dec_int(&light->col.b, i, gen_lim(0, 255));
	return (0);
}
