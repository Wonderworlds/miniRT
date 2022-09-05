/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:30:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 21:34:40 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"

void	bp_ambient(t_menu *menu)
{
	menu->bprint[0] = '0';
	menu->bprint[1] = '1';
	menu->bprint[2] = '0';
	menu->bprint[3] = '1';
	menu->bprint[4] = '1';
	menu->bprint[5] = '1';
	menu->bprint[6] = 0;
}

void	bp_light(t_menu *menu)
{
	menu->bprint[0] = '1';
	menu->bprint[1] = '0';
	menu->bprint[2] = '1';
	menu->bprint[3] = '1';
	menu->bprint[4] = '1';
	menu->bprint[5] = '0';
	menu->bprint[6] = '1';
	menu->bprint[7] = '0';
	menu->bprint[8] = '1';
	menu->bprint[9] = '1';
	menu->bprint[10] = '1';
	menu->bprint[11] = 0;
}

void	bp_plane(t_menu *menu)
{
	menu->bprint[0] = '1';
	menu->bprint[1] = '0';
	menu->bprint[2] = '1';
	menu->bprint[3] = '1';
	menu->bprint[4] = '1';
	menu->bprint[5] = '0';
	menu->bprint[6] = '1';
	menu->bprint[7] = '1';
	menu->bprint[8] = '1';
	menu->bprint[9] = '0';
	menu->bprint[10] = '1';
	menu->bprint[11] = '1';
	menu->bprint[12] = '1';
	menu->bprint[13] = 0;
}

void	bp_sphere(t_menu *menu)
{
	menu->bprint[0] = '1';
	menu->bprint[1] = '0';
	menu->bprint[2] = '1';
	menu->bprint[3] = '1';
	menu->bprint[4] = '1';
	menu->bprint[5] = '0';
	menu->bprint[6] = '1';
	menu->bprint[7] = '0';
	menu->bprint[8] = '1';
	menu->bprint[9] = '1';
	menu->bprint[10] = '1';
	menu->bprint[11] = 0;
}

void	bp_cylinder(t_menu *menu)
{
	menu->bprint[0] = '1';
	menu->bprint[1] = '0';
	menu->bprint[2] = '1';
	menu->bprint[3] = '1';
	menu->bprint[4] = '1';
	menu->bprint[5] = '0';
	menu->bprint[6] = '1';
	menu->bprint[7] = '1';
	menu->bprint[8] = '1';
	menu->bprint[9] = '0';
	menu->bprint[10] = '1';
	menu->bprint[11] = '1';
	menu->bprint[12] = '0';
	menu->bprint[13] = '1';
	menu->bprint[14] = '1';
	menu->bprint[15] = '1';
	menu->bprint[16] = 0;
}
