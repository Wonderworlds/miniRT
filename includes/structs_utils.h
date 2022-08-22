/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:04:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/22 16:50:41 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_UTILS_H
# define STRUCTS_UTILS_H

# include "libft.h"

typedef struct s_pos
{
	float	x;
	float	y;
	float	z;

}	t_pos;

typedef struct s_rgb
{
	short unsigned int	r;
	short unsigned int	g;
	short unsigned int	b;

}	t_rgb;

typedef enum e_type
{
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
	t_rgb			col;
}	t_vol;

typedef struct s_cam
{
	t_pos			pos;
	t_pos			vec3;
	unsigned int	h_fov;
}	t_cam;

typedef struct s_light
{
	char		ambient;
	t_rgb		col;
	float		r;
	t_pos		pos;
}	t_light;

typedef struct s_scene
{
	t_list	*vols;
	t_list	*lights;
	t_cam	cam;
	//struct bvh_root;
}	t_scene;

#endif
