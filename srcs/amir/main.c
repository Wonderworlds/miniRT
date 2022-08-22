/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/08/22 15:21:33 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"

int	main(int ac, char **av)
{
	t_scene	scene;
	
	if (ac != 2)
	{
		ft_fprintf(2, "Invalid arg\n");
		return (EXIT_FAILURE);
	}
	parse_rt(av[1], &scene);
	graphic_process(&scene);
	return (0);
}
