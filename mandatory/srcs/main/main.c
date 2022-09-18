/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/09/18 02:43:28 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "minirt.h"
#include "mlx_data.h"

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
	graphic_process(&scene);
	leave_rt(&scene);
	return (EXIT_SUCCESS);
}
