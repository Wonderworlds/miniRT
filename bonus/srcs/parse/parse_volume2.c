/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_volume2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:30:53 by amahla            #+#    #+#             */
/*   Updated: 2022/09/13 14:05:10 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "utils.h"
#include "libft.h"

static void	triangle_normal(t_vol *tr)
{
	t_pos vec3[2];

	vector_ab(tr->tr[0], tr->tr[1], &vec3[0]);
	vector_ab(tr->tr[0], tr->tr[2], &vec3[1]);
	cross_product(vec3[0], vec3[1], &tr->vec3);
	unit_vector(&tr->vec3);
}

void	triangle(t_scene *scene, char *str)
{
	t_vol	*tr;
	int		i;

	i = 2;
	malloc_volume(&tr, scene, TRIANGLE);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &tr->tr[0], str + i);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &tr->tr[1], str + i);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &tr->tr[2], str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &tr->col, str + i);
	while (str[i] == ' ')
		i++;
	parse_vol_texture(scene, tr, str + i);
	triangle_bounds_and_set(tr);
	triangle_normal(tr);
}
