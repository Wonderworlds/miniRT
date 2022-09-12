/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:19:09 by amahla            #+#    #+#             */
/*   Updated: 2022/09/12 23:54:57 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"

float	phong_reflection(t_hit hit_from_camera, t_pos dir_light,
	t_light *lights, t_cam *cam)
{
	t_pos	r;
	t_pos	temp[2];
	float	coeff;

	vector_equal(dir_light, &temp[0]);
	vector_scale(-1, &temp[0]);
	vector_equal(hit_from_camera.normal, &temp[1]);
	coeff = dot_product(hit_from_camera.normal, temp[0]);
	coeff *= 2;
	vector_scale(coeff, &temp[1]);
	vector_sub(temp[1], temp[0], &r);
	coeff = lights->r * powf(fmaxf(0.f, dot_product(r, cam->vec3))
		, hit_from_camera.spec.size);
	coeff *= hit_from_camera.spec.intensity;
	return (coeff);

}
