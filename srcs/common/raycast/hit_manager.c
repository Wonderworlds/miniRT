/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:47:23 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 20:02:01 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

static float	hit_manager(int action, t_hit *ptr, float newdst)
{
	static t_hit	_hit = {-1, {0,0,0}};

	if (action == 2)
		_hit.dst_origin = newdst;
	else if (action == 1)
		hit_cpy(ptr, &_hit);
	else if (action == 0 && ptr)
		hit_cpy(&_hit, ptr);
	return (_hit.dst_origin);
}

static void	set_hit(t_hit *ptr, int newdst)
{
	hit_manager(1, ptr, newdst);
}

void	reset_hit(void)
{
	hit_manager(2, NULL, -1);
}

float	get_hit(t_hit *ptr)
{
	return (hit_manager(0, ptr, 0));
}

void	update_hit(t_hit *ptr)
{
	float	dst;

	dst = get_hit(NULL);
	if (dst > ptr->dst_origin || dst == -1)
		set_hit(ptr, ptr->dst_origin);
}
