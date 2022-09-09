/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_volume2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:30:53 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 20:08:33 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "utils.h"
#include "libft.h"

void	triangle(t_scene *scene, char *str)
{
	t_vol	*tr;
	int		i;

	i = 2;
	malloc_volume(&tr, scene, 2);
	tr->type = TRIANGLE;
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
//	unit_vector(&tr->vec3);
//	triangle_bounds(tr);
	ft_lstadd_back(&scene->vols, ft_lstnew(tr));
}
