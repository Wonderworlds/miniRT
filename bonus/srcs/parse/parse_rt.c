/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:18:09 by amahla            #+#    #+#             */
/*   Updated: 2022/09/13 17:10:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "utils.h"
#include "structs_utils.h"
#include "libft.h"
#include "bvh.h"

void	exit_parse(t_scene *scene, const char *error)
{
	if (!error)
		ft_fprintf(2, "Error\nError parse format\n");
	else
		ft_fprintf(2, "%s", error);
	leave_rt(scene);
	close(scene->fd);
	exit(EXIT_FAILURE);
}

void	exit_parse_cam(t_scene *scene, char *str)
{
	ft_lstclear(&scene->lights, &free);
	ft_lstclear(&scene->vols, &free);
	ft_lstclear(&scene->cameras, &free);
	close(scene->fd);
	ft_fprintf(2, "%s", str);
	exit(EXIT_FAILURE);
}

int	open_file(char *arg)
{
	int	size;
	int	fd;

	size = ft_strlen(arg);
	if (size < 4 || ft_strncmp(arg + size - 3, ".rt", 3) != 0)
		error_msg("Error\nInvalid format: expected '.rt'\n");
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		error_msg("Error\nopen: error file\n");
	return (fd);
}

void	read_rt(int fd, t_scene *scene)
{
	char	*str;

	str = ft_gnl_rt(fd);
	if (!str)
		error_msg("Error\nfile: empty\n");
	while (str)
	{
		scene->line_gnl = str;
		if (str[0] == 'A' && str[1] == ' ')
			ambient_lightning(scene, str);
		else if (str[0] == 'R' && str[1] == ' ')
			resolution(scene, str);
		else if ((str[0] == 'c' || str[0] == 'C') && str[1] == ' ')
			camera(scene, str);
		else if ((str[0] == 'l' || str[0] == 'L') && str[1] == ' ')
			light(scene, str);
		else if (str[0] == 's' && str[1] == 'p' && str[2] == ' ')
			sphere(scene, str);
		else if (str[0] == 'p' && str[1] == 'l' && str[2] == ' ')
			plane(scene, str);
		else if (str[0] == 'c' && str[1] == 'y' && str[2] == ' ')
			cylinder(scene, str);
		else if (str[0] == 't' && str[1] == 'r' && str[2] == ' ')
			triangle(scene, str);
		else if (str[0] != '\n' && str[0] != '#')
			exit_parse(scene, NULL);
		free(str);
		str = ft_gnl_rt(fd);
	}
	scene->line_gnl = NULL;
}

void	parse_rt(char *arg, t_scene *scene)
{
	int	fd;
	int	size;

	fd = open_file(arg);
	scene->fd = fd;
	read_rt(fd, scene);
	if (!scene->cam)
		exit_parse_cam(scene,
			"Error\nError parse format: camera 'C' is not set\n");
	if (scene->resolut.is_set == false)
	{
		scene->resolut.win_width = 1500;
		scene->resolut.aspect_ratio = 16.0 / 9.0;
		scene->resolut.win_height = 1500 / scene->resolut.aspect_ratio;
	}
	size = ft_lstsize(scene->vols) - 1;
	if (size >= 0)
	{
		ft_printf("START bvh\n");
		build_node(&scene->vols, &scene->bvh, 0, (unsigned int)size);
		if (!scene->bvh)
			exit_parse_cam(scene, "Error\nmalloc fail\n");
	}
	close(fd);
}
