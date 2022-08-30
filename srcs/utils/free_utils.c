/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:03:50 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 17:10:31 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include <stdlib.h>

void	free_vol(void *vol)
{
	if (vol)
		free((t_vol *)vol);
}

void	free_light(void *light)
{
	if (light)
		free((t_light *)light);
}

void	free_plane(t_plane *pl)
{
	if (pl)
		free((t_plane *)pl);
}