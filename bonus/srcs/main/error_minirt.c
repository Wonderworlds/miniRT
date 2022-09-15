/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_minirt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:03:03 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 00:29:29 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

void	error_mlx_data(t_data *data, void *mlx_ptr)
{
	if (mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(mlx_ptr);
	}
	ft_fprintf(2, "Error\nMlx data initialize error\n");
	leave_rt(data->scene);
	exit(EXIT_FAILURE);
}

void	exit_parse(t_scene *scene, const char *error)
{
	if (!error)
		ft_fprintf(2, "Error\nError parse format\n");
	else
		ft_fprintf(2, "%s", error);
	leave_rt(scene);
	close(scene->fd);
	exit(EXIT_FAILURE);
}

void	exit_parse_cam(t_scene *scene, char *str)
{
	ft_lstclear(&scene->lights, &free);
	ft_lstclear(&scene->vols, &free);
	ft_lstclear(&scene->cameras, &free);
	close(scene->fd);
	ft_fprintf(2, "%s", str);
	exit(EXIT_FAILURE);
}
