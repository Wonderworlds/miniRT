/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:10:20 by amahla            #+#    #+#             */
/*   Updated: 2022/09/05 21:58:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DATA_H
# define MLX_DATA_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "structs_utils.h"
# include "mlx.h"

# define WIN_WIDTH 1400
# define ASPECT_RATIO (16.0f / 9.0f)
# define WIN_HEIGHT WIN_WIDTH / ASPECT_RATIO
# define VP_WIDTH 3.0f
# define FOCAL_LENGTH 2.0f

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_menu
{
	t_bool	is_visible;
	t_img	menu_img;
	int		item;
	int		index;
	int		field_index;
	int		max_f_index;
	char	bprint[17];
}			t_menu;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_scene	*scene;
	t_menu	menu;
}			t_data;

//		graphics/error_mlx.c
void	error_mlx_data(t_data *data, void *mlx_ptr);

//		graphics/graphics_process.c
int		graphic_process(t_scene *scene);

//		graphics/graphic_render.c
int		img_pix_put(t_img *img, int x, int y, int color);
int		graphic_render(t_data *data);

//		graphics/graphic_hook.c
void	handle_hooks(t_data *data);

//		menu/graphic_menu.c
int		display_menu(t_data *data, t_menu *menu, t_scene *scene);

#endif
