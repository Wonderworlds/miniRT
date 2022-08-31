/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_volume.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/08/31 14:00:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

void	malloc_volume(t_vol **vol, t_scene *scene)
{
	*vol = malloc(sizeof(t_vol));
	if (!vol)
		exit_parse(scene);
}

void	malloc_pl(t_plane **pl, t_scene *scene)
{
	*pl = malloc(sizeof(t_plane));
	if (!pl)
		exit_parse(scene);
}

void	sphere(t_scene *scene, char *str)
{
	t_vol	*sp;
	int		i;

	i = 2;
	malloc_volume(&sp, scene);
	sp->type = SPHERE;
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &sp->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &sp->d, str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &sp->col, str + i);
	sphere_bounds(sp);
	ft_lstadd_back(&scene->vols, ft_lstnew(sp));
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
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &pl->col, str + i);
	ft_lstadd_back(&scene->planes, ft_lstnew(pl));
}

void	cylinder(t_scene *scene, char *str)
{
	t_vol	*cy;
	int		i;

	i = 2;
	malloc_volume(&cy, scene);
	cy->type = CYLINDER;
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &cy->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_vec3(scene, &cy->vec3, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &cy->d, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &cy->h, str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &cy->col, str + i);
	cylinder_bounds(cy);
	ft_lstadd_back(&scene->vols, ft_lstnew(cy));
}
