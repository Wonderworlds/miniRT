/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_volume.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/08/23 21:42:47 by ammah            ###   ########.fr       */
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
	ft_lstadd_back(scene->vols, ft_lstnew(sp));
}

void	plane(t_scene *scene, char *str)
{
	t_vol	*pl;
	int		i;

	i = 2;
	malloc_volume(&pl, scene);
	pl->type = PLANE;
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &pl->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_vec3(scene, &pl->vec3, str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &pl->col, str + i);
	ft_lstadd_back(scene->vols, ft_lstnew(pl));
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
	ft_lstadd_back(scene->vols, ft_lstnew(cy));
}
