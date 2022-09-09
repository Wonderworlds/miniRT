/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_leave.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 22:44:33 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "utils.h"
#include "bvh.h"

void	init_scene(t_scene *scene)
{
	scene->vols = NULL;
	scene->lights = NULL;
	scene->cameras = NULL;
	scene->ambient = NULL;
	scene->planes = NULL;
	scene->bvh = NULL;
	scene->cam = NULL;
	scene->resolut.is_set = false;
}

void	leave_rt(t_scene *scene)
{
	ft_lstclear(&scene->lights, &free);
	ft_lstclear(&scene->vols, &free);
	ft_lstclear(&scene->planes, &free);
	ft_lstclear(&scene->cameras, &free);
	if (scene->ambient)
		free(scene->ambient);
	btree_remove_infix(&scene->bvh, &free);
}
