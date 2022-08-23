/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:04:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/22 21:44:56 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <fcntl.h>
#include "structs_utils.h"

//		parse/parse_rt.c
void	parse_rt(char *arg, t_scene *scene);
void	exit_parse(t_scene *scene);

//		parse/format_data.c
bool	pos_format(char *str);
bool	r_format(char *str);
bool	rgb_format(char *str);
bool	h_fov_format(char *str);
bool	float_format(char *str);

//		parse/set_variables
int		set_pos(t_scene *scene, t_pos *pos, char *str);
int		set_vec3(t_scene *scene, t_pos *vec3, char *str);
int		set_rgb(t_scene *scene, t_rgb *col, char *str);
int		set_float(t_scene *scene, float *data, char *str);
int		set_h_fov(t_scene *scene, int *data, char *str);

//		parse/parse_volume.c
void	sphere(t_scene *scene, char *str);
void	plane(t_scene *scene, char *str);
void	cylinder(t_scene *scene, char *str);

//		parse/parse_light.c
void	ambient_lightning(t_scene *scene, char *str);
void	light(t_scene *scene, char *str);

//		parse/parse_camera.c
void	camera(t_scene *scene, char *str);

#endif