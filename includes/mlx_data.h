/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:10:20 by amahla            #+#    #+#             */
/*   Updated: 2022/08/22 16:57:34 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <X11/X.h>
# include <X11/keysym.h>
# include "structs_utils.h"
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
