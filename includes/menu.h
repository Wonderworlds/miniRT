/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:45:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 18:14:06 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

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
	m_vol,
	m_plane
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

#endif