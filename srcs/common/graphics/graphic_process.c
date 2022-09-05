/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/09/05 16:42:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"

void init_menu(t_menu *menu)
{
	menu->is_visible = false;
	menu->index = 0;
	menu->item = 0;
	menu->field_index = 0;
	ft_memset(&menu->bprint, 0, 15);
}

int	graphic_process(t_scene *scene)
{
	t_data	data;

	data.scene = scene;
	init_menu(&data.menu);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		error_mlx_data(&data, NULL);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data.win_ptr)
		error_mlx_data(&data, data.mlx_ptr);
	mlx_set_font(data.mlx_ptr, data.win_ptr, "10x20");
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	handle_hooks(&data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
