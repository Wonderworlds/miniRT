/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:06:57 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 20:08:06 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "minirt.h"
#include "libft.h"

void	resolution(t_scene *scene, char *str)
{
	int	i;

	i = 1;
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]) || ft_atoi_err(str + i, &scene->resolut.win_width) || scene->resolut.win_width < 1 || scene->resolut.win_width > 1920) 
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ' ')
		exit_parse(scene, NULL);
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]) || ft_atoi_err(str + i, &scene->resolut.win_height) || scene->resolut.win_height < 1 || scene->resolut.win_height > 1080) 
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\n')
		exit_parse(scene, NULL);
	scene->resolut.aspect_ratio = scene->resolut.win_width;
	scene->resolut.aspect_ratio /= scene->resolut.win_height;
	scene->resolut.is_set = true;
}
