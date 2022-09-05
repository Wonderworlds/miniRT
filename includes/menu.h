/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:45:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/06 00:03:52 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "mlx_data.h"

#define WHITE_PIXEL 13158600
#define BLACK_PIXEL 2631720
#define GREYD_PIXEL 4276545
#define GREY_PIXEL 9868950
#define BG_PIXEL BLACK_PIXEL
#define BGFIELD_PIXEL GREYD_PIXEL
#define SELFIELD_PIXEL GREY_PIXEL
#define FONT_PIXEL WHITE_PIXEL

#define RECT_START_X 10
#define RECT_END_X (RECT_START_X + 200)
#define RECT_START_Y 20

#define FOFFSET_Y 5
#define FOFFSET_X 10
#define FOFFSET_TITLE_X RECT_START_X + FOFFSET_X * 4
#define FOFFSET_1_X RECT_START_X + FOFFSET_X
#define FOFFSET_MID_X (RECT_END_X / 2) + RECT_START_X

#define STEP_FIELD 26

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
	int	minX;
	int	maxX;
	int	minY;
	int	maxY;
}	t_rect;

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
void 	fill_field(t_data *data, int y, void *item, int type);
void	fill_camera(t_data *data, t_cam *cam, int y_start);
void	fill_ambient(t_data *data, t_list *lg, int y_start);
void	fill_light(t_data *data, t_list *lg, int y_start);
void	fill_vol(t_data *data, t_list *lvol, int y_start);

//		menu/fill_menu.c
int		fill_template(t_data *data, int y_start, char *name,
			const int type);
void	fill_menu(t_menu *menu, t_data *data, t_scene *scene);

//		menu/add_dec_menu.c
void	add_dec(void *value, int type, int op);
int		add_dec_cam(t_data *data, int i);
int		add_dec_ambient(t_data *data, int i);
int		add_dec_light(t_data *data, int i);
int		add_dec_sphere(t_data *data, int i);

//		menu/add_dec_menu2.c
int		check_lst_index(t_list *lst, int *index, int i);
int		add_dec_plane(t_data *data, int i);
int		add_dec_cylinder(t_data *data, int i);
#endif