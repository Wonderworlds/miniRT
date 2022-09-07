/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:03:03 by amahla            #+#    #+#             */
/*   Updated: 2022/09/07 13:19:07 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "minirt.h"

void	error_mlx_data(t_data *data, void *mlx_ptr)
{
	(void)data;
	if (mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(mlx_ptr);
	}
	ft_fprintf(2, "Error\nMlx data initialize error\n");
	leave_rt(data->scene);
	exit(EXIT_FAILURE);
}
