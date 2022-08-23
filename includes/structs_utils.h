/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:04:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/23 21:37:25 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_UTILS_H
# define STRUCTS_UTILS_H

# include "libft.h"

typedef int	bool;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_pos
{
	float	x;
	float	y;
	float	z;

}	t_pos;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;

}	t_rgb;

typedef enum e_type
{
	AMB_LIGHT,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_vol
{
	t_type	type;
	t_pos	pos;
	t_pos	vec3;
	float	d;
	float	h;
	t_rgb	col;
}	t_vol;

typedef struct s_cam
{
	t_pos	pos;
	t_pos	vec3;
	int		h_fov;
	bool	is_set;
}	t_cam;

typedef struct s_light
{
	t_type		type;
	t_rgb		col;
	float		r;
	t_pos		pos;
}	t_light;

typedef struct s_scene
{
	t_list	**vols;
	t_list	**lights;
	t_cam	cam;
	int		fd;
	char	*line_gnl;
	//struct bvh_root;
}	t_scene;

#endif
