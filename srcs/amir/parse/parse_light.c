/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:19:36 by amahla            #+#    #+#             */
/*   Updated: 2022/08/23 00:01:30 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"
#include <stdio.h>

void	ambient_lightning(t_scene *scene, char *str)
{
	t_light	a;
	t_list	*lights;
	t_light	*temp;
	int		i;

	i = 1;
	lights = scene->lights;
	while (lights)
	{
		temp = lights->content;
		if (temp->type == AMB_LIGHT)
			exit_parse(scene);
		lights = lights->next;
	}
	a.type = AMB_LIGHT;
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &a.r, str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &a.col, str + i);
	ft_lstadd_back(&scene->lights, ft_lstnew(&a));
}

void	light(t_scene *scene, char *str)
{
	t_light	l;
	t_list	*lights;
	t_light	*temp;
	int		i;

	i = 1;
	lights = scene->lights;
	while (lights)
	{
		temp = lights->content;
		if (temp->type == LIGHT)
			exit_parse(scene);
		lights = lights->next;
	}
	l.type = LIGHT;
	while (str[i] == ' ')
		i++;
	i += set_pos(scene, &l.pos, str + i);
	while (str[i] == ' ')
		i++;
	i += set_float(scene, &l.r, str + i);
	while (str[i] == ' ')
		i++;
	i += set_rgb(scene, &l.col, str + i);
	ft_lstadd_back(&scene->lights, ft_lstnew(&l));
}
