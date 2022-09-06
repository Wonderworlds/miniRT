/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dec_menu3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:17:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/06 16:01:26 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include "menu.h"

void	add_dec_float(float *value, int op, t_delim lim)
{
	if (op == 1)
	{
		*value += 0.1f;
		if (*value > lim.max)
		{
			if (*value == lim.max + 0.1f)
				*value = lim.min;
			else
				*value = lim.max;
		}
	}
	else
	{
		*value -= 0.1f;
		if (*value < lim.min)
		{
			if (*value == lim.min - 0.1f)
				*value = lim.max;
			else
				*value = lim.min;
		}
	}
}

void	add_dec_int(int *value, int op, t_delim lim)
{
	if (op == 1)
	{
		*value += 1;
		if (*value > lim.max)
			*value = lim.min;
	}
	else
	{
		*value -= 1;
		if (*value < lim.min)
			*value = lim.max;
	}
}

t_delim	gen_lim(int min, int max)
{
	t_delim	ret;

	ret.min = min;
	ret.max = max;
	return (ret);
}
