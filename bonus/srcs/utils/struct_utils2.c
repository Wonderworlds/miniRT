/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:28:09 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/10 17:12:09 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"

t_couple	gen_couple(int x, int y)
{
	t_couple	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}