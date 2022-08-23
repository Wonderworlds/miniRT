/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:03:03 by amahla            #+#    #+#             */
/*   Updated: 2022/08/22 16:51:06 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"

void	error_mlx_data(t_data *data, void *mlx_ptr)
{
	(void)data;
	if (mlx_ptr)
		free(mlx_ptr);
	ft_fprintf(2, "data initialize error\n");
	exit(EXIT_FAILURE);
}
