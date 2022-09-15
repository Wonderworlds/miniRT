/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dec_menu3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:59:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"
#include "utils.h"

void	add_dec_double(double *value, int op, t_delim lim)
{
	if (op == 1)
	{
		*value += 0.1f;
		if (*value > lim.max)
		{
			if (*value == lim.max + 0.1f)
				*value = lim.min;
			else
				*value = lim.max;
		}
	}
	else
	{
		*value -= 0.1f;
		if (*value < lim.min)
		{
			if (*value == lim.min - 0.1f)
				*value = lim.max;
			else
				*value = lim.min;
		}
	}
}

void	add_dec_int(int *value, int op, t_delim lim)
{
	if (op == 1)
	{
		*value += 1;
		if (*value > lim.max)
			*value = lim.min;
	}
	else
	{
		*value -= 1;
		if (*value < lim.min)
			*value = lim.max;
	}
}

t_delim	gen_lim(int min, int max)
{
	t_delim	ret;

	ret.min = min;
	ret.max = max;
	return (ret);
}

void	update_unit_vector(t_mitem type, t_scene *scene)
{
	t_list	*index;
	t_vol	*vol;

	if (type == m_cam)
		unit_vector(&scene->cam->vec3);
	else if (type == m_plane && scene->planes)
	{
		index = scene->planes;
		while (index)
		{
			unit_vector(&((t_plane *)index->content)->vec3);
			index = index->next;
		}
	}
	else if (type == m_vol)
	{
		index = scene->vols;
		while (index)
		{
			vol = (t_vol *)index->content;
			if (vol->type == CYLINDER)
				unit_vector(&vol->vec3);
			index = index->next;
		}
	}
}
