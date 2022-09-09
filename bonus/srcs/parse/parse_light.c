/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 22:22:44 by fmauguin         ###   ########.fr       */
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
	a->type = AMB_LIGHT;
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &a->r, str + i, 0);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &a->col, str + i);
	scene->ambient = a;
}

void	light(t_scene *scene, char *str)
{
	t_light	*l;
	t_list	*lights;
	int		i;

	i = 1;
	lights = scene->lights;
	malloc_light(&l, scene);
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
	ft_lstadd_back(&scene->lights, ft_lstnew(l));
}
