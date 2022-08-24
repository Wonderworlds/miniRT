/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:54:16 by amahla            #+#    #+#             */
/*   Updated: 2022/08/24 17:41:08 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	sphere_bounds(t_vol sp, t_box *box)
{
	float	r;

	r = sp.d / 2;
	set_vector(r, r, r, &box->max);
	set_vector(-r, -r, -r, &box->min);
	vector_add(sp.pos, box->max, &box->max);
	vector_add(sp.pos, box->min, &box->min);
	vector_ab(box->min, box->max, &box->size);
}

void	cylinder_bounds(t_vol pl, t_box *box)
{
	float	dim_h;
	float	r;

	m_h = pl.h / 2;
	r = pl.d / 2;
