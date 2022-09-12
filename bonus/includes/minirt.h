/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:04:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/12 11:39:37 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include "structs_utils.h"

# define ALBEDO 0.3f

//		main/start_and_leave.c
void	init_scene(t_scene *scene);
void	leave_rt(t_scene *scene);

//		parse/parse_rt.c
void	parse_rt(char *arg, t_scene *scene);
void	exit_parse(t_scene *scene, const char *error);

//		parse/format_data.c
t_bool	pos_format(char *str);
t_bool	r_format(char *str);
t_bool	rgb_format(char *str);
t_bool	h_fov_format(char *str);
t_bool	float_format(char *str);

//		parse/set_variables
int		set_pos(t_scene *scene, t_pos *pos, char *str);
int		set_vec3(t_scene *scene, t_pos *vec3, char *str);
int		set_rgb(t_scene *scene, t_rgb *col, char *str);
int		set_float(t_scene *scene, float *data, char *str, int option);
int		set_h_fov(t_scene *scene, int *data, char *str);

//		parse/parse_volume.c
void	malloc_volume(t_vol **vol, t_scene *scene, int option);
void	sphere(t_scene *scene, char *str);
void	plane(t_scene *scene, char *str);
void	cylinder(t_scene *scene, char *str);

//		parse/parse_volume2.c
void	triangle(t_scene *scene, char *str);

//		parse/parse_light.c
void	ambient_lightning(t_scene *scene, char *str);
void	light(t_scene *scene, char *str);

//		parse/parse_camera.c
void	camera(t_scene *scene, char *str);

//		parse/parse_texture.c
void	parse_pl_texture(t_scene *scene, t_plane *pl, char *str);
void	parse_vol_texture(t_scene *scene, t_vol *vol, char *str);

//		parse/resolution.c
void	resolution(t_scene *scene, char *str);

//		volume/inside_vol.c
t_bool	inside_vol(t_pos *pos, t_vol *volume);

//		volume/bounds.c
void	update_bounds_vol(t_list *vols);
void	sphere_bounds(t_vol *sp);
void	cylinder_bounds(t_vol *cy);

//		volume/bounds_total.c
void	bounds_total(t_list *vols, t_box *box,
			unsigned int begin, unsigned int end);

//		volume/intersect.c
t_bool	plane_and_sphere_intersect(t_vol pl, t_vol vol);

//		raycast/hit_manager.c
void	update_hit(t_hit *ptr);
float	get_hit(t_hit *ptr);
void	reset_hit(void);

//		raycast/ray_volume_hit.c
t_bool	is_aabb_hit(t_ray ray, t_box aabb);
t_bool	is_sphere_hit(t_ray *ray, t_vol *sp);
t_bool	is_plane_hit(t_ray *ray, t_plane *pl);

//		raycast/ray_cylinder_hit.c
void	check_cylinder_extremity(t_vol *cy, t_pos cy_top, t_ray *ray);

//		raycast/ray_cylinder_hit2.c
t_bool	is_cylinder_hit(t_ray *ray, t_vol *cy);

//		raycast//create_hit.c
void	create_hit(float t, t_vol *vol, t_plane *pl, t_ray *ray);

//		raycast/ray_print.c
void	create_ray(const t_pos origin, const t_pos dir, t_ray *ray);
int		find_volume(t_bvh *root, t_ray ray);
void	find_plane(t_list *pl, t_ray *ray);
t_rgb	ray_render(int y, int x, t_cam *cam, t_scene *scene);

//		lights/lights.c
t_rgb	add_lights(t_scene *scene, t_hit *hit);

//		light/phong_reflection.c
t_pos	phong_reflection(t_hit hit_from_camera, t_pos dir_light,
	t_light *lights, t_cam *cam);


#endif
