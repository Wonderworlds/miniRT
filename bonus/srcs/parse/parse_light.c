/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/21 13:59:01 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"
#include <stdio.h>

void	malloc_light(t_light **light, t_scene *scene)
{
	*light = malloc(sizeof(t_light));
	if (!*light)
		exit_parse(scene, "Error\nmalloc fail\n");
}

void	ambient_lightning(t_scene *scene, char *str)
{
	int		i;
	t_light	*a;

	i = 1;
	if (scene->ambient)
		exit_parse(scene, NULL);
	malloc_light(&a, scene);
	scene->ambient = a;
	a->type = AMB_LIGHT;
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &a->r, str + i, 0);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &a->col, str + i);
	a->r_o = a->r;
}

void	light(t_scene *scene, char *str)
{
	t_light	*l;
	int		i;

	i = 1;
	malloc_light(&l, scene);
	ft_lstadd_back(&scene->lights, ft_lstnew(l));
	l->type = LIGHT;
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &l->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &l->r, str + i, 0);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &l->col, str + i);
	l->r_o = l->r;
}
