/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/08/30 14:42:20 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"

int	graphic_process(t_scene *scene)
{
	t_data	data;

	data.scene = scene;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		error_mlx_data(&data, NULL);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data.win_ptr)
		error_mlx_data(&data, data.mlx_ptr);
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
