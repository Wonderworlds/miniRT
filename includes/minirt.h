/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:04:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/30 16:13:32 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include "structs_utils.h"

//		parse/parse_rt.c
void			parse_rt(char *arg, t_scene *scene);
void			exit_parse(t_scene *scene);

//		parse/format_data.c
t_bool			pos_format(char *str);
t_bool			r_format(char *str);
t_bool			rgb_format(char *str);
t_bool			h_fov_format(char *str);
t_bool			float_format(char *str);

//		parse/set_variables
int				set_pos(t_scene *scene, t_pos *pos, char *str);
int				set_vec3(t_scene *scene, t_pos *vec3, char *str);
int				set_rgb(t_scene *scene, t_rgb *col, char *str);
int				set_float(t_scene *scene, float *data, char *str);
int				set_h_fov(t_scene *scene, int *data, char *str);

//		parse/parse_volume.c
void			sphere(t_scene *scene, char *str);
void			plane(t_scene *scene, char *str);
void			cylinder(t_scene *scene, char *str);

//		parse/parse_light.c
void			ambient_lightning(t_scene *scene, char *str);
void			light(t_scene *scene, char *str);

//		parse/parse_camera.c
void			camera(t_scene *scene, char *str);

//		volume/inside_vol.c
t_bool			inside_vol(t_pos *pos, t_vol *volume);

//		volume/bounds.c
void			sphere_bounds(t_vol *sp);
void			cylinder_bounds(t_vol *cy);

//		volume/bounds_total.c
void			bounds_total(t_list *vols, t_box *box,
					unsigned int begin, unsigned int end);

//		volume/intersect.c
t_bool			plane_and_sphere_intersect(t_vol pl, t_vol vol);

//		raycast/hit_manager.c
void			update_hit(t_hit *ptr);
float			get_hit(t_hit *ptr);
void			reset_hit(void);

//		raycast/hit_manager.c
t_bool			is_aabb_hit(t_ray ray, t_box aabb);
t_bool			is_sphere_hit(t_ray *ray, t_vol *sp);

//		raycast/ray_print.c
t_rgb			ray_render(int y, int x, t_cam cam);
#endif
