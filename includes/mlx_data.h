/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:10:20 by amahla            #+#    #+#             */
/*   Updated: 2022/08/31 16:44:38 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DATA_H
# define MLX_DATA_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "structs_utils.h"
# include "mlx.h"

# define WIN_WIDTH 1500
# define ASPECT_RATIO (16.0 / 9.0)
# define WIN_HEIGHT WIN_WIDTH / ASPECT_RATIO
# define VIEWPORT_HEIGHT VIEWPORT_WIDTH / ASPECT_RATIO
# define VIEWPORT_WIDTH 3.0
# define FOCAL_LENGTH 1


typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_scene	*scene;
}			t_data;

//		graphics/error_mlx.c
void	error_mlx_data(t_data *data, void *mlx_ptr);

//		graphics/graphics_process.c
int		graphic_process(t_scene *scene);

//		graphics/graphic_render.c
int		graphic_render(t_data *data);

//		graphics/graphic_hook.c
void	handle_hooks(t_data *data);

#endif
