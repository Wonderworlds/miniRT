/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:42:26 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/27 16:04:50 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "utils.h"
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

// int	main(void)
// {
// 	t_pos	pos = {0, 0, 0};
// 	t_pos	pt1 = {5, 5, 5};
// 	t_pos	pt2 = {2.5f, 2.5f, 2.5f};
// 	t_pos	pt3 = {0, 0, 10};
// 	t_pos	pt4 = {7, 7, 17};
// 	t_pos	vec = {0, 0, 1};

// 	ft_printf("Sphere inside test\n");
// 	t_vol a;
// 	create_sphere(&a, 10, pos);
// 	print_vol(&a);
// 	ft_printf("%d\n", inside_vol(&pos, &a));
// 	ft_printf("%d\n", inside_vol(&pt1, &a));
// 	ft_printf("%d\n", inside_vol(&pt2, &a));

// 	ft_printf("\nplane inside test\n");
// 	t_vol b;
// 	create_plane(&b, pos, vec);
// 	print_vol(&b);
// 	ft_printf("%d\n", inside_vol(&pos, &b));
// 	ft_printf("%d\n", inside_vol(&pt1, &b));
// 	ft_printf("%d\n", inside_vol(&pt2, &b));

// 	ft_printf("\nCylinder inside test\n");
// 	t_vol c;
// 	create_cylinder(&c, pos, vec, 10, 6);
// 	print_vol(&c);
// 	ft_printf("%d\n", inside_vol(&pos, &c));
// 	ft_printf("%d\n", inside_vol(&pt3, &c));
// 	ft_printf("%d\n", inside_vol(&pt1, &c));
// 	ft_printf("%d\n", inside_vol(&pt2, &c));
// 	ft_printf("%d\n", inside_vol(&pt4, &c));
// 	return (0);
// }

//sphere test tri
int main(void)
{
	t_list	*lst;
	t_vol	a, b, c, d, e;
	t_pos	pos = {0, 0, 0};
	t_pos	pos2 = {10, 0, 0};
	t_pos	pos3 = {1, 1, 0};
	t_pos	pos4 = {-2, 1, 0};
	t_pos	pos5 = {0, 7, 0};
	t_box	box_total;
	unsigned int m;

	lst = NULL;
	create_sphere(&a, 10, pos);
	create_sphere(&b, 10, pos2);
	create_sphere(&c, 10, pos3);
	create_sphere(&d, 10, pos4);
	create_sphere(&e, 10, pos5);
	sphere_bounds(&a);
	sphere_bounds(&b);
	sphere_bounds(&c);
	sphere_bounds(&d);
	sphere_bounds(&e);
	ft_lstadd_front(&lst, ft_lstnew((void *)&a));
	ft_lstadd_front(&lst, ft_lstnew((void *)&b));
	ft_lstadd_front(&lst, ft_lstnew((void *)&c));
	ft_lstadd_front(&lst, ft_lstnew((void *)&d));
	ft_lstadd_front(&lst, ft_lstnew((void *)&e));
	// ft_lstiter(lst, print_vol);
	// print_vol(&a);
	bounds_total(lst, &box_total, 0, ft_lstsize(lst) - 1);
	ft_fprintf(2, "\nbounds total\n");
	print_pos(&box_total.center, "center box");
	print_pos(&box_total.min, "   min box");
	print_pos(&box_total.max, "   max box");

	m = sort_vols(&lst, &box_total);
	ft_printf("\nm = %u\n", m);
	print_vol(ft_lst_at(lst, m)->content);
	// ft_lstiter(lst, print_vol);
}

// //cylinder
// int main(void)
// {
// 	t_list	*lst;
// 	t_vol	a, b, c, d;
// 	t_pos	pos = {0, 0, 0};
// 	t_pos	vec = {0, 0, 1};
// 	t_pos	pos2 = {6, 0, 0};
// 	// t_pos	pos3 = {0, 5, 5};
// 	// t_pos	pos4 = {0, -5, -5};
// 	t_box	box_total;

// 	lst = NULL;
// 	create_cylinder(&a, pos, vec, 10, 6);
// 	create_cylinder(&b, pos2, vec, 10, 6);
// 	create_cylinder(&c, pos, vec, 10, 6);
// 	create_cylinder(&d, pos, vec, 10, 6);
// 	cylinder_bounds(&a);
// 	cylinder_bounds(&b);
// 	cylinder_bounds(&c);
// 	cylinder_bounds(&d);
// 	ft_lstadd_front(&lst, ft_lstnew((void *)&a));
// 	ft_lstadd_front(&lst, ft_lstnew((void *)&b));
// 	ft_lstadd_front(&lst, ft_lstnew((void *)&c));
// 	ft_lstadd_front(&lst, ft_lstnew((void *)&d));
// 	// ft_lstiter(lst, print_vol);
// 	print_vol(&a);
// 	bounds_total(lst, &box_total, 0, ft_lstsize(lst) - 1);
// 	ft_fprintf(2, "\nbounds total\n");
// 	print_pos(&box_total.center, "center box");
// 	print_pos(&box_total.min, "   min box");
// 	print_pos(&box_total.max, "   max box");
// }
