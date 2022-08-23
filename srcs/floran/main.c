/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:42:26 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/23 19:25:52 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "minirt.h"
#include <stdio.h>

void	create_sphere(t_vol *sp, float d, t_pos pos)
{
	sp->type = SPHERE;
	sp->pos.x = pos.x;
	sp->pos.y = pos.y;
	sp->pos.z = pos.z;
	sp->d = d;
}

void	create_plane(t_vol *pl, t_pos pos, t_pos vec)
{
	pl->type = PLANE;
	pl->pos.x = pos.x;
	pl->pos.y = pos.y;
	pl->pos.z = pos.z;
	pl->vec3.x = vec.x;
	pl->vec3.y = vec.y;
	pl->vec3.z = vec.z;
}

void	create_cylinder(t_vol *cy, t_pos pos, t_pos vec, float h, float d)
{
	cy->type = CYLINDER;
	cy->pos.x = pos.x;
	cy->pos.y = pos.y;
	cy->pos.z = pos.z;
	cy->vec3.x = vec.x;
	cy->vec3.y = vec.y;
	cy->vec3.z = vec.z;
	cy->d = d;
	cy->h = h;
}

int main(void)
{
 	t_pos pos = {0, 0, 0};
 	t_pos pt1 = {5, 5, 5};
 	t_pos pt2 = {2.5f, 2.5f, 2.5f};

	t_vol a;
	create_sphere(&a, 10, pos);
	ft_printf("%d\n", inside_vol(pos, a));
	ft_printf("%d\n", inside_vol(pt1, a));
	ft_printf("%d\n", inside_vol(pt2, a));
	return (0);
}