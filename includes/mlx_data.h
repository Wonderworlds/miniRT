/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:10:20 by amahla            #+#    #+#             */
/*   Updated: 2022/08/22 15:22:03 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <X11/X.h>
# include <X11/keysym.h>
//# include <fcntl.h>
//# include <errno.h>
//# include <stdio.h>
# include "mlx.h"

# define WIN_HEIGHT 600
# define WIN_WIDTH 800

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}			t_data_mlx;

//		error.c
void	error_mlx_data(t_point **map, int height_map, void *to_free_1,
			void *to_free_2);
void	error_malloc_strs(char **map);
void	error_malloc_strs2(t_point **map_int, char **map, int j);

//		parse_fdf.c
t_point	**parse_fdf(char *arg, int *width_map, int *height_map);

//		fdf.c
int		set_color(t_point **map, t_data *data);

//		graphics_process.c
int		graphic_process(t_point **map, int width_map, int height_map);

//		graphic_render.c
int		render(t_data *data);

//		graphic_hook.c
void	handle_hooks(t_data *data);

#endif
