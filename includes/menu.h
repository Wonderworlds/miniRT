/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:45:17 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 16:40:17 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

#define WHITE_PIXEL 13158600
#define BLACK_PIXEL 2631720
#define GREYD_PIXEL 4276545
#define GREY_PIXEL 6579300
#define BG_PIXEL BLACK_PIXEL
#define BGFIELD_PIXEL GREYD_PIXEL
#define SELFIELD_PIXEL GREY_PIXEL
#define FONT_PIXEL WHITE_PIXEL

#define RECT_START_X 10
#define RECT_END_X (RECT_START_X + 200)
#define RECT_START_Y 20

#define FOFFSET_Y 5
#define FOFFSET_X 10

#define STEP_FIELD 25

typedef enum e_menu_item
{
	m_cam,
	m_ambient,
	m_light,
	m_vol,
	m_plane
}	t_mitem;

typedef struct s_rect
{
	int	minX;
	int	maxX;
	int	minY;
	int	maxY;
}	t_rect;

#endif