/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:28:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/25 19:50:54 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"

void	pos_cpy(const t_pos *src, t_pos *dest)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

void	col_cpy(const t_rgb *src, t_rgb *dest)
{
	dest->r = src->r;
	dest->g = src->g;
	dest->b = src->b;
}

void	box_cpy(const t_box *src, t_box *dest)
{
	dest->rayon = src->rayon;
	pos_cpy(&src->center, &dest->center);
}

void	vol_cpy(const t_vol *src, t_vol *dest)
{
	dest->type = src->type;
	dest->type = src->type;
	dest->d = src->d;
	dest->h = src->h;
	box_cpy(&src->box, &dest->box);
	pos_cpy(&src->pos, &dest->pos);
	pos_cpy(&src->vec3, &dest->vec3);
	col_cpy(&src->col, &dest->col);
}
