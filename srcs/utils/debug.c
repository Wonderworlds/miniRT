/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:04:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/26 13:37:10 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "libft.h"
#include <stdio.h>

void	print_pos(t_pos *pos, const char *str)
{
	printf("| %s:\t| %f | %f | %f |\n", str, pos->x, pos->y, pos->z);
}

static void	print_sp(t_vol *sp)
{
	printf("SPHERE\n");
	printf("| diametre:\t%f\n", sp->d);
	printf("--------------------------------------------------\n");
	printf("| name\t\t| x\t   | y\t      | z\t |\n");
	print_pos(&sp->pos, "center");
	printf("--------------------------------------------------\n");
}

static void	print_pl(t_vol *pl)
{
	printf("PLANE\n");
	printf("--------------------------------------------------\n");
	printf("| name\t\t| x\t   | y\t      | z\t |\n");
	print_pos(&pl->pos, "origin");
	print_pos(&pl->vec3, "normal");
	printf("--------------------------------------------------\n");
}

static void	print_cy(t_vol *cy)
{
	printf("CYLINDER\n");
	printf("| rayon:\t%f\n", cy->d);
	printf("| height:\t%f\n", cy->h);
	printf("--------------------------------------------------\n");
	printf("| name\t\t| x\t   | y\t      | z\t |\n");
	print_pos(&cy->pos, "origin");
	print_pos(&cy->vec3, "normal");
	printf("--------------------------------------------------\n");
}

void	print_vol(t_vol *vol)
{
	void (*f[3])(t_vol *);

	f[0] = &print_sp;
	f[1] = &print_pl;
	f[2] = &print_cy;
	f[vol->type - SPHERE](vol);
}