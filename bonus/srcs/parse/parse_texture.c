/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:22:21 by amahla            #+#    #+#             */
/*   Updated: 2022/09/09 20:12:20 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "utils.h"
#include "libft.h"
#include "mlx_data.h"

static int	check_and_set_texture(char *str, t_xpm *tex)
{
	int	i;

	i = 0;
	if (ft_strlen_rt(str) < 13)
		return (-2);
	if (ft_strncmp("texture:", str, 8) != 0
		&& ft_strncmp("bumpmap:", str, 8) != 0
		&& ft_strncmp("disruption:", str, 11) != 0)
		return (-2);
	if (ft_strncmp("texture:", str, 8) != 0)
		return (-1);
	str += 8;
	while (str[i] && !(str[i] == '\n' || str[i] == '.' || str[i] == ' '))
		i++;
	if (str[i] != '.' || (str[i] == '.' && ft_strlen_rt(str + i) < 4
		&& ft_strncmp(".xpm", str + i, 4) != 0))
		return (-2);
	tex->file = malloc(sizeof(char) * (i + 4 + 1));
	if (!tex->file)
		return (-3);
	ft_strlcpy(tex->file, str, i + 4 + 1);
	while (str[i + 4] && str[i + 4] == ' ')
		i++;
	return (i + 4 + 8);
}

static int	check_and_set_bump(char *str, t_xpm *bump)
{
	int	i;

	i = 0;
	if (ft_strlen_rt(str) < 13)
		return (-2);
	if (ft_strncmp("texture:", str, 8) != 0
		&& ft_strncmp("bumpmap:", str, 8) != 0
		&& ft_strncmp("disruption:", str, 11) != 0)
		return (-2);
	if (ft_strncmp("bumpmap:", str, 8) != 0)
		return (-1);
	str += 8;
	while (str[i] && !(str[i] == '\n' || str[i] == '.' || str[i] == ' '))
		i++;
	if (str[i] != '.' || (str[i] == '.' && ft_strlen_rt(str + i) < 4
		&& ft_strncmp(".xpm", str + i, 4) != 0))
		return (-2);
	bump->file = malloc(sizeof(char) * (i + 4 + 1));
	if (!bump->file)
		return (-3);
	ft_strlcpy(bump->file, str, i + 4 + 1);
	while (str[i + 4] && str[i + 4] == ' ')
		i++;
	return (i + 4 + 8);
}

static int	check_and_set_disruption(char *str, t_disruption *disruption)
{
	int	i;

	i = 0;
	if (ft_strlen_rt(str) < 13)
		return (-2);
	if (ft_strncmp("texture:", str, 8) != 0
		&& ft_strncmp("bumpmap:", str, 8) != 0
		&& ft_strncmp("disruption:", str, 11) != 0)
		return (-2);
	if (ft_strncmp("disruption:", str, 11) != 0)
		return (-1);
	str += 11;
	while (str[i] && !(str[i] == '\n' || str[i] == ' '))
		i++;
	if (i == 4 && ft_strncmp("none", str, 4) == 0)
		*disruption = NONE;
	else if (i == 5 && ft_strncmp("other", str, 5) == 0)
		*disruption = OTHER;
	else if (i == 12 && ft_strncmp("checkerboard", str, 12) == 0)
		*disruption = CHECKERBOARD;
	else
		return (-2);
	while (str[i] == ' ')
		i++;
	return (i + 11);
}

void	parse_vol_texture(t_scene *scene, t_vol *vol, char *str)
{
	int	i;
	int		exit_status;
	int		time;

	time = 3;
	i = 0;
	vol->tex.file = NULL;
	vol->bump.file = NULL;
	vol->disruption = NO_SET;
	while (time--)
	{
		if (!str[i] || str[i] == '\n')
			return ;
		exit_status = check_and_set_texture(str + i, &vol->tex);
		if (exit_status == -1)
			exit_status = check_and_set_bump(str + i, &vol->bump);
		if (exit_status == -1)
			exit_status = check_and_set_disruption(str + i, &vol->disruption);
		if (exit_status == -2 || exit_status == -3)
		{
			if (vol->tex.file)
				free(vol->tex.file);
			if (vol->bump.file)
				free(vol->bump.file);
			if (exit_status == -2)
				exit_parse(scene, NULL);
			else
				exit_parse(scene, "Error\nmalloc fail\n");
		}
		i += exit_status;
	}
}


void	parse_pl_texture(t_scene *scene, t_plane *pl, char *str)
{
	int	i;
	int		exit_status;
	int		time;

	i = 0;
	time = 3;
	pl->tex.file = NULL;
	pl->bump.file = NULL;
	pl->disruption = NO_SET;
	while (time--)
	{
		if (!str[i] || str[i] == '\n')
			return ;
		exit_status = check_and_set_texture(str + i, &pl->tex);
		if (exit_status == -1)
			exit_status = check_and_set_bump(str + i, &pl->bump);
		if (exit_status == -1)
			exit_status = check_and_set_disruption(str + i, &pl->disruption);
		if (exit_status == -2 || exit_status == -3)
		{
			if (pl->tex.file)
				free(pl->tex.file);
			if (pl->bump.file)
				free(pl->bump.file);
			if (exit_status == -2)
				exit_parse(scene, NULL);
			else
				exit_parse(scene, "Error\nmalloc fail\n");
		}
		i += exit_status;
	}
}
