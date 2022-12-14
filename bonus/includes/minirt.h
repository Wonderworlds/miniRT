/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:04:08 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 18:37:27 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include "structs_utils.h"

//		main/start_and_leave.c
void	init_scene(t_scene *scene);
void	leave_rt(t_scene *scene);

//		main/error_minirt.c
void	exit_parse(t_scene *scene, const char *error);
void	exit_parse_cam(t_scene *scene, char *str);

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
void	malloc_volume(t_vol **vol, t_scene *scene, t_type type);
void	sphere(t_scene *scene, char *str);
void	plane(t_scene *scene, char *str);
void	cylinder(t_scene *scene, char *str);

//		parse/parse_volume2.c
void	triangle(t_scene *scene, char *str);
void	cone(t_scene *scene, char *str);

//		parse/parse_light.c
void	ambient_lightning(t_scene *scene, char *str);
void	light(t_scene *scene, char *str);

//		parse/parse_camera.c
void	camera(t_scene *scene, char *str);

//		parse/parse_texture.c
void	parse_pl_texture(t_scene *scene, t_plane *pl, char *str);
void	parse_vol_texture(t_scene *scene, t_vol *vol, char *str);

//		parse/parse_texture2.c
size_t	set_specular(t_scene *scene, char *str, t_spec *spec);
size_t	set_t_xpm(t_scene *scene, char *str, t_xpm **xpm);

//		parse/resolution.c
void	resolution(t_scene *scene, char *str);

//		volume/inside_vol.c
t_bool	inside_vol(t_pos *pos, t_vol *volume);

//		volume/bounds.c
void	sphere_bounds(t_vol *sp);
void	cylinder_bounds(t_vol *cy);
void	cone_bounds(t_vol *cy);

//		volume/bounds2.c
void	update_bounds_vol(t_list *vols);
void	triangle_bounds_and_set(t_vol *tr);

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
float	solve_quadratic(float a, float b, float c);
t_bool	is_aabb_hit(t_ray ray, t_box aabb);
t_bool	is_sphere_hit(t_ray *ray, t_vol *sp);
t_bool	is_plane_hit(t_ray *ray, t_plane *pl);

//		raycast/ray_cylinder_hit.c
float	set_t(t_pos *e, t_pos cy, t_ray *ray, t_pos cy_vec3);
float	set_t2(float dot, float denom, t_bool *dir, t_bool sign);
void	check_cylinder_extremity(t_vol *cy, t_pos cy_top, t_ray *ray);

//		raycast/ray_cylinder_hit2.c
t_bool	is_cylinder_hit(t_ray *ray, t_vol *cy);

//		raycast/ray_cone_hit.c
t_bool	is_cone_hit(t_ray *ray, t_vol *hy);

//		raycast/ray_triangle_hit.c
t_bool	is_triangle_hit(t_ray *ray, t_vol *tr);

//		raycast//create_hit.c
void	create_hit(float t, t_vol *vol, t_plane *pl, t_ray *ray);

//		raycast//create_hit2.c
void	hit_triangle(t_vol *vol, t_hit *hit);
void	hit_cone(t_vol *vol, t_hit *hit);
void	hit_sphere(t_vol *vol, t_hit *hit);
void	hit_cylinder(t_vol *vol, t_hit *hit);
void	hit_plane(t_plane *pl, t_hit *hit);

//		raycast/ray_print.c
void	create_ray(const t_pos origin, const t_pos dir, t_ray *ray);
int		find_volume(t_bvh *root, t_ray ray);
void	find_plane(t_list *pl, t_ray *ray);
t_rgb	ray_render(int y, int x, t_cam *cam, t_scene *scene);

//		lights/lights.c
void	add_coeficient(t_pos *rgb, float coef, t_rgb *col);
t_rgb	add_lights(t_scene *scene, t_hit *hit);

//		light/phong_reflection.c
float	phong_reflection(t_hit hit_from_camera, t_pos dir_light,
			t_light *lights, t_cam *cam);

//		light/disruption.c
void	do_disruption(t_hit *hit);

//		light/disruption2.c
void	checkerboard(t_couplef uv, t_hit *hit);
void	get_uvw_sp(t_hit *hit, t_vol *sp, t_couplef *uv);
void	get_uvw_pl(t_hit *hit, t_plane *pl, t_couplef *uv);
void	get_uvw_tr(t_hit *hit, t_vol *tr, t_couplef *uv);

//		light/texture_col.c
void	do_tex_bump(t_hit *hit);
void	bump_map(t_hit *hit, t_light *light);

//		lights/get_uv.c
void	get_uv_sp(t_hit *hit, t_vol *sp, t_couplef *uv, t_xpm *xpm);
void	get_uv_cy(t_hit *hit, t_vol *cy, t_couplef *uv, t_xpm *xpm);
void	get_uv_pl(t_hit *hit, t_plane *pl, t_couplef *uv, t_xpm *xpm);
void	get_uv_tr(t_hit *hit, t_vol *tr, t_couplef *uv, t_xpm *xpm);
void	get_uv_co(t_hit *hit, t_vol *tr, t_couplef *uv, t_xpm *xpm);

//		lights/antialiasing.c
void	write_color(t_rgb *pixel_color, t_resolut *res);
void	rand_f(t_resolut *res, int index, t_couplef *uv);

#endif
