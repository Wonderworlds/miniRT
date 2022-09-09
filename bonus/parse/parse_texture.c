/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:22:21 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 15:50:40 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "utils.h"
#include "libft.h"

int	check_and_set_texture(char *str, t_vol *vol)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str) < 13)
		return (1);
	if (ft_strncmp("texture:", str, 8) != 0)
		return (1)
	str += 8;
	while (str[i] && !(str[i] == '\n' || str[i] == '.' || str[i] == ' '))
		i++;
	if (str[i] != '.' && ft_strlen(str + i) < 4
		&& ft_strncmp(".xpm", str + i, 4) != 0)
		return (1);
	vol->xpm.file = malloc(sizeof(char) * (i + 4 + 1));
	if (!vol->xpm.file)
		return (-1);
	ft_strlcpy(vol->xpm.file, str, i + 4 + 1);
	return (i + 4);
}

int	check_and_set_bump(char *str, t_vol *vol)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str) < 13)
		return (1);
	if (ft_strncmp("bumpmap:", str, 8) != 0)
		return (1)
	str += 8;
	while (str[i] && !(str[i] == '\n' || str[i] == '.' || str[i] == ' '))
		i++;
	if (str[i] != '.' && ft_strlen(str + i) < 4
		&& ft_strncmp(".xpm", str + i, 4) != 0)
		return (1);
	vol->xpm.file = malloc(sizeof(char) * (i + 4 + 1));
	if (!vol->xpm.file)
		return (-1);
	ft_strlcpy(vol->bump.file, str, i + 4 + 1);
	return (i + 4);
}
	
void	parse_vol_texture(t_scene *scene, t_vol *vol, char *str)
{
	if (ft_strlen(str) 
