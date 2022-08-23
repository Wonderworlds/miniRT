/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:42:26 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/23 15:55:32 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int main(int ac, char **av)
{
	float f = 0;

	if (ac == 1)
		return (1);
	if (ft_atof(av[1], &f))
		return (1);
	printf("%f\n", f);
	return (0);
}