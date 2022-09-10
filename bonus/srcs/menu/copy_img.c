/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:04:02 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/10 18:52:33 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "mlx_data.h"
#include "utils.h"

static void	copy_img(t_img_c *img, t_rect *rect, int *new_addr, int action);

static int	*save_img_manager(void)
{
	static int	saved_img[57201];

	return (&saved_img[0]);
}

void	set_save_img(t_img_c *img, t_rect rect)
{
	copy_img(img, &rect, save_img_manager(), 1);
}

void	get_save_img(t_img_c *img, t_rect rect)
{
	copy_img(img, &rect, save_img_manager(), 0);
}

static void	copy_img(t_img_c *img, t_rect *rect, int *new_addr, int action)
{
	char	*pixel;
	int		x;
	size_t	i;

	i = 0;
	while (--rect->max_y >= rect->min_y)
	{
		x = rect->min_x;
		while (x++ < rect->max_x)
		{
			pixel = img->addr
				+ (rect->max_y * img->line_len + x * (img->bpp / 8));
			if (action == 1)
				*(new_addr + i++) = *(int *)pixel;
			else
				*((int *)pixel) = *(new_addr + i++);
		}
	}
}
