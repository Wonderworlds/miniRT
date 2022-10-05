/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:20:12 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/22 14:52:05 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "stdio.h"


int main(int ac, char **av)
{
	if (ac == 2)
	{
		float n = 0;
		if (ft_atof(av[1], &n))
			return (1);
		printf("%f\n", n);
	}
	ft_fprintf(2, "Hello World!\n");
	return (0);
}