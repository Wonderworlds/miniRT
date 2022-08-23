/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/08/23 12:13:36 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"
#include <stdio.h>

void	malloc_light(t_light **light, t_scene *scene)
{
	*light = malloc(sizeof(t_light));
	if (!light)
		exit_parse(scene);
}

void	ambient_lightning(t_scene *scene, char *str)
{
	t_light	*a;
	t_list	*lights;
	t_light	*temp;
	int		i;

	i = 1;
	lights = *(scene->lights);
	while (lights)
	{
		temp = (t_light *)(lights->content);
		if (temp->type == AMB_LIGHT)
			exit_parse(scene);
		lights = lights->next;
	}
	malloc_light(&a, scene);
	a->type = AMB_LIGHT;
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &a->r, str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &a->col, str + i);
	ft_lstadd_back(scene->lights, ft_lstnew(a));
}

void	light(t_scene *scene, char *str)
{
	t_light	*l;
	t_list	*lights;
	t_light	*temp;
	int		i;

	i = 1;
	lights = *(scene->lights);
	while (lights)
	{
		temp = lights->content;
		if (temp->type == LIGHT)
			exit_parse(scene);
		lights = lights->next;
	}
	malloc_light(&l, scene);
	l->type = LIGHT;
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &l->pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &l->r, str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &l->col, str + i);
	ft_lstadd_back(scene->lights, ft_lstnew(l));
}
