/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:23:53 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:10:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

void	bbox_center(const t_box *box, t_pos *center)
{
	vector_ab(box->min, box->max, center);
	center->x = box->min.x + center->x / 2;
	center->y = box->min.y + center->y / 2;
	center->z = box->min.z + center->z / 2;
}

double	bbox_expend(const t_box *box)
{
	return (dist_ab(&box->min, &box->max));
}
