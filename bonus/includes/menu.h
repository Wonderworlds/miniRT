/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:45:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:10:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "mlx_data.h"
# include "structs_utils.h"

# define WHITE_PIXEL 13158600
# define BLACK_PIXEL 2631720
# define GREYD_PIXEL 4276545
# define GREY_PIXEL 9868950
# define BG_PIXEL 2631720
# define BGFIELD_PIXEL 4276545
# define SELFIELD_PIXEL 9868950
# define FONT_PIXEL 13158600

# define RECT_START_X 10
# define RECT_END_X 210
# define RECT_START_Y 20
# define RECT_START_Y2 176
# define RECT_END_Y2 462

# define FOFFSET_Y 5
# define FOFFSET_X 10
# define FOFFSET_TITLE_X 50
# define FOFFSET_1_X 20
# define FOFFSET_MID_X 115

# define STEP_FIELD 26

typedef enum e_menu_item
{
	m_cam,
	m_ambient,
	m_light,
	m_plane,
	m_vol
}	t_mitem;

typedef enum e_m_key
{
	m_int,
	m_float,
	m_t_pos,
	m_t_rgb,
}	t_m_key;

typedef struct s_rect
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}	t_rect;

typedef struct s_delim
{
	int	min;
	int	max;
}	t_delim;

//		menu/build_menu.c
t_rect	gen_rect(int minX, int maxX, int minY, int maxY);
void	rect_display(t_data *data, t_rect rect, int color);
void	display_field(t_data *data, t_menu *menu, size_t size);
void	select_field(t_data *data, t_menu *menu, size_t size);

//		menu/bp_utils.c
void	bp_ambient(t_menu *menu);
void	bp_light(t_menu *menu);
void	bp_plane(t_menu *menu);
void	bp_sphere(t_menu *menu);
void	bp_cylinder(t_menu *menu);

//		menu/fill_menu2.c
void	fill_field(t_data *data, int y, void *item, int type);
void	fill_camera(t_data *data, t_cam *cam, int y_start);
void	fill_ambient(t_data *data, t_light *lg, int y_start);
void	fill_light(t_data *data, t_list *lg, int y_start);
void	fill_vol(t_data *data, t_list *lvol, int y_start);

//		menu/fill_menu.c
int		fill_template(t_data *data, int y_start, char *name,
			const int type);
void	fill_menu(t_menu *menu, t_data *data, t_scene *scene);

//		menu/add_dec_menu.c
int		add_dec_cam(t_data *data, int i);
int		add_dec_ambient(t_data *data, int i);
int		add_dec_light(t_data *data, int i);
int		add_dec_sphere(t_data *data, int i);

//		menu/add_dec_menu2.c
int		check_lst_index(t_list *lst, int *index, int i);
int		add_dec_plane(t_data *data, int i);
int		add_dec_cylinder(t_data *data, int i);

//		menu/add_dec_menu3.c
void	add_dec_float(double *value, int op, t_delim lim);
void	add_dec_int(int *value, int op, t_delim lim);
t_delim	gen_lim(int min, int max);
void	update_unit_vector(t_mitem type, t_scene *scene);

//		menu/graphic_menu.c
void	graphic_refresh(t_data *data, t_delim x, t_delim y);

void	get_save_img(t_img_c *img, t_rect rect);
void	set_save_img(t_img_c *img, t_rect rect);

#endif
