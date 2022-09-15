/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_volume2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:30:53 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 01:09:35 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "utils.h"
#include "libft.h"

static void	triangle_normal(t_vol *tr)
{
	t_pos	vec3[2];

	vector_ab(tr->tr[0], tr->tr[1], &vec3[0]);
	vector_ab(tr->tr[0], tr->tr[2], &vec3[1]);
	cross_product(vec3[0], vec3[1], &tr->vec3);
	unit_vector(&tr->vec3);
}

void	sphere(t_scene *scene, char *str)
{
	t_vol	*sp;
	int		i;

	i = 2;
	malloc_volume(&sp, scene, SPHERE);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &sp->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &sp->d, str + i, 1);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &sp->col, str + i);
	while (str[i] == ' ')
		i++;
	parse_vol_texture(scene, sp, str + i);
	sphere_bounds(sp);
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

static void	cone2(t_scene *scene, int i, char *str, t_vol *co)
{
	i += set_float(scene, &co->d, str + i, 1);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &co->h, str + i, 1);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &co->col, str + i);
	while (str[i] == ' ')
		i++;
	parse_vol_texture(scene, co, str + i);
	unit_vector(&co->vec3);
	cone_bounds(co);
}

void	cone(t_scene *scene, char *str)
{
	t_vol	*co;
	int		i;

	i = 2;
	malloc_volume(&co, scene, CONE);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &co->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_vec3(scene, &co->vec3, str + i);
	if (co->vec3.x == 0 && co->vec3.y == 0 && co->vec3.z == 0)
		co->vec3.y = 1.f;
	while (str[i] == ' ')
		i++;
	cone2(scene, i, str, co);
}
