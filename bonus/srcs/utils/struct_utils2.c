/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:28:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/12 15:58:31 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"

t_couple	gen_couple(int x, int y)
{
	t_couple	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

void	set_color(int r, int g, int b, t_rgb *col)
{
	col->r = r;
	col->g = g;
	col->b = b;
}
