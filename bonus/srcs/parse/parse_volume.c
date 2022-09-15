/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_volume.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/12 23:46:15 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "utils.h"
#include "libft.h"

void	malloc_volume(t_vol **vol, t_scene *scene, t_type type)
{
	t_list *elem;

	elem = NULL;
	*vol = malloc(sizeof(t_vol));
	if (!*vol)
		exit_parse(scene, "Error\nmalloc fail\n");
	elem = ft_lstnew(*vol);
	if (!elem)
		exit_parse(scene, "Error\nmalloc fail\n");
	ft_lstadd_back(&scene->vols, elem);
	(*vol)->type = type;
	(*vol)->bump = NULL;
	(*vol)->tex = NULL;
	(*vol)->data = NULL;
	(*vol)->disruption = NONE;
	(*vol)->spec.size = 0;
	(*vol)->spec.intensity = 0.f;
}

void	malloc_pl(t_plane **pl, t_scene *scene)
{
	t_list *elem;

	elem = NULL;
	*pl = malloc(sizeof(t_plane));
	if (!*pl)
		exit_parse(scene, "Error\nmalloc fail\n");
	elem = ft_lstnew(*pl);
	if (!elem)
		exit_parse(scene, "Error\nmalloc fail\n");
	ft_lstadd_back(&scene->planes, elem);
	(*pl)->bump = NULL;
	(*pl)->tex = NULL;
	(*pl)->data = NULL;
	(*pl)->spec.size = 0;
	(*pl)->spec.intensity = 0.f;
}

void	sphere(t_scene *scene, char *str)
{
	t_vol	*sp;
	int		i;

	i = 2;
	malloc_volume(&sp, scene, SPHERE);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &sp->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &sp->d, str + i, 1);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &sp->col, str + i);
	while (str[i] == ' ')
		i++;
	parse_vol_texture(scene, sp, str + i);
	sphere_bounds(sp);
}

void	plane(t_scene *scene, char *str)
{
	t_plane	*pl;
	int		i;

	i = 2;
	malloc_pl(&pl, scene);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &pl->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_vec3(scene, &pl->vec3, str + i);
	if (pl->vec3.x == 0 && pl->vec3.y == 0 && pl->vec3.z == 0)
		pl->vec3.y = 1.f;
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &pl->col, str + i);
	while (str[i] == ' ')
		i++;
	parse_pl_texture(scene, pl, str + i);
	unit_vector(&pl->vec3);
}

void	cylinder(t_scene *scene, char *str)
{
	t_vol	*cy;
	int		i;

	i = 2;
	malloc_volume(&cy, scene, CYLINDER);
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &cy->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_vec3(scene, &cy->vec3, str + i);
	if (cy->vec3.x == 0 && cy->vec3.y == 0 && cy->vec3.z == 0)
		cy->vec3.y = 1.f;
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &cy->d, str + i, 1);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &cy->h, str + i, 1);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &cy->col, str + i);
	while (str[i] == ' ')
		i++;
	parse_vol_texture(scene, cy, str + i);
	unit_vector(&cy->vec3);
	cylinder_bounds(cy);
}
