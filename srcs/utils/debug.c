/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:04:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/26 18:02:57 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "libft.h"
#include <stdio.h>

void	print_pos(const t_pos *pos, const char *str)
{
	printf("| %s:\t| %f\t| %f\t| %f\t|\n", str, pos->x, pos->y, pos->z);
}

static void	print_sp(const t_vol *sp)
{
	printf("\nSPHERE\n");
	printf("| diametre:\t%f\n", sp->d);
	printf("-----------------------------------------------------------------\n");
	printf("| vol\t\t| x\t\t| y\t\t| z\t\t|\n");
	print_pos(&sp->pos, "center");
	printf("-----------------------------------------------------------------\n");
	printf("| box\t\t| x\t\t| y\t\t| z\t\t|\n");
	print_pos(&sp->box.center, "center");
	print_pos(&sp->box.min, "   min");
	print_pos(&sp->box.max, "   max");
	printf("-----------------------------------------------------------------\n");
}

static void	print_pl(const t_vol *pl)
{
	printf("\nPLANE\n");
	printf("-----------------------------------------------------------------\n");
	printf("| name\t\t| x\t\t| y\t\t| z\t\t|\n");
	print_pos(&pl->pos, "origin");
	print_pos(&pl->vec3, "normal");
	printf("-----------------------------------------------------------------\n");
	printf("| box\t\t| x\t\t| y\t\t| z\t\t|\n");
	print_pos(&pl->box.center, "center");
	print_pos(&pl->box.min, "   min");
	print_pos(&pl->box.max, "   max");
	printf("-----------------------------------------------------------------\n");
}

static void	print_cy(const t_vol *cy)
{
	printf("\nCYLINDER\n");
	printf("| rayon:\t%f\n", cy->d);
	printf("| height:\t%f\n", cy->h);
	printf("-----------------------------------------------------------------\n");
	printf("| name\t\t| x\t\t| y\t\t| z\t\t|\n");
	print_pos(&cy->pos, "origin");
	print_pos(&cy->vec3, "normal");
	printf("-----------------------------------------------------------------\n");
	printf("| box\t\t| x\t\t| y\t\t| z\t\t|\n");
	print_pos(&cy->box.center, "center");
	print_pos(&cy->box.min, "   min");
	print_pos(&cy->box.max, "   max");
	printf("-----------------------------------------------------------------\n");
}

void	print_vol(void *vol)
{
	void	(*f[3])(const t_vol *);
	t_vol	*volume;

	volume = (t_vol *)vol;
	f[0] = &print_sp;
	f[1] = &print_pl;
	f[2] = &print_cy;
	f[volume->type - SPHERE](volume);
}
