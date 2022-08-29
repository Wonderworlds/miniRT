/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:47:23 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 19:17:22 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

static int	hit_manager(int action, t_hit *ptr, int newdst)
{
	static t_hit	_hit;
	static int		dst = -1;

	if (action == 2)
		dst = newdst;
	else if (action == 1)
	{
		hit_cpy(ptr, &_hit);
		dst = newdst;
	}
	else if (action == 0 && ptr)
		hit_cpy(&_hit, ptr);
	return (dst);
}

static void	set_hit(t_hit *ptr, int newdst)
{
	hit_manager(1, ptr, newdst);
}

void	reset_hit(void)
{
	hit_manager(2, NULL, -1);
}

int	get_hit(t_hit *ptr)
{
	return (hit_manager(ptr, 0, 0));
}

void	update_hit(t_hit *ptr, t_pos *cam)
{
	int	dst;
	int	dst2;

	dst = get_hit(NULL);
	dst2 = dist_ab(ptr, cam);
	if (dst > dst2 || dst == -1)
		set_hit(ptr, dst2);
}
