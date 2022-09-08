/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/09/08 17:32:50 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "minirt.h"
#include "utils.h"
#include "mlx_data.h"
#include "bvh.h"

void	init_scene(t_scene *scene)
{
	scene->vols = NULL;
	scene->lights = NULL;
	scene->ambient = NULL;
	scene->planes = NULL;
	scene->bvh = NULL;
	scene->cam.is_set = false;
}

void	leave_rt(t_scene *scene)
{
	ft_lstclear(&scene->lights, &free);
	ft_lstclear(&scene->vols, &free);
	ft_lstclear(&scene->planes, &free);
	if (scene->ambient)
		free(scene->ambient);
	btree_remove_infix(&scene->bvh, &free);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	init_scene(&scene);
	if (ac != 2)
	{
		if (ac < 2)
			ft_fprintf(2, "Error\nMaps needed\n");
		else
			ft_fprintf(2, "Error\nToo many maps to load\nPlease choose one\n");
		return (EXIT_FAILURE);
	}
	parse_rt(av[1], &scene);
	print_bvh("", scene.bvh, 0);
///*	----> test parse <-----
	check_value(scene);
//	----------------------- */

	graphic_process(&scene);
	leave_rt(&scene);
	return (0);
}
