/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:28:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 19:52:20 by fmauguin         ###   ########.fr       */
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
	pos_cpy(&src->center, &dest->center);
	pos_cpy(&src->min, &dest->min);
	pos_cpy(&src->max, &dest->max);
	dest->expend = src->expend;
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

void	hit_cpy(const t_hit *src, t_hit *dest)
{
	col_cpy(&src->col, &dest->col);
	dest->dst_origin = src->dst_origin;
}