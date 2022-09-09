/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:10:20 by amahla            #+#    #+#             */
/*   Updated: 2022/09/07 17:02:59 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DATA_H
# define MLX_DATA_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "structs_utils.h"
# include "mlx.h"

# define WIN_WIDTH 1400
# define ASPECT_RATIO 1.78f
# define WIN_HEIGHT 786
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
	t_bool	has_changed;
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

//		parse/parse_camera.c
void	set_camera(t_cam *cam);

//		graphics/error_mlx.c
void	error_mlx_data(t_data *data, void *mlx_ptr);

//		graphics/graphics_process.c
int		graphic_process(t_scene *scene);

//		graphics/graphic_render.c
int		img_pix_put(t_img *img, int x, int y, int color);
int		graphic_render(t_data *data);
int		get_color(t_rgb color);

//		graphics/graphic_hook.c
void	handle_hooks(t_data *data);
int		exit_hook(t_data *data);

//		menu/graphic_menu.c
int		display_menu(t_data *data, t_menu *menu, t_scene *scene);

//		menu/event_menu.c
void	close_menu(t_data *data);
void	open_menu(t_data *data);
void	switch_menu(t_data *data);
void	updown_menu(t_data *data, int i);
void	left_right_menu(t_data *data, int i);

#endif
