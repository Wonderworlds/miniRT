/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_coord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:45:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/10 18:08:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"

void	get_tex_pixel_sp(t_xpm *xpm, t_hit *hit)
{

}

void	get_tex_pixel_pl(t_xpm *xpm, t_hit *hit)
{

}

void	get_tex_pixel_cy(t_xpm *xpm, t_hit *hit)
{

}

void	get_tex_pixel(t_type type, t_xpm *xpm, t_hit *hit)
{
	void	(*f[3])(t_xpm *, t_hit *);
	int		index;

	index = type - SPHERE;
	f[0] = &get_tex_pixel_sp;
	f[1] = &get_tex_pixel_pl;
	f[2] = &get_tex_pixel_cy;
	(*f[index])(xpm, hit);
}