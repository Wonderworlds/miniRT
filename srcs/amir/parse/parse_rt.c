/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:18:09 by amahla            #+#    #+#             */
/*   Updated: 2022/08/23 14:13:16 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

void	error_format(char *str)
{
	ft_fprintf(2, "%s", str);
	exit(EXIT_FAILURE);
}

void	exit_parse(t_scene *scene)
{
	ft_lstclear(scene->lights, &free);
	ft_lstclear(scene->vols, &free);
	close(scene->fd);
	ft_fprintf(2, "Error\nError parse format\n");
	exit(EXIT_FAILURE);
}

int	open_file(char *arg)
{
	int	size;
	int	fd;

	size = ft_strlen(arg);
	if (size < 4 || ft_strncmp(arg + size - 3, ".rt", 3) != 0)
		error_format("Error\nInvalid format: expected '.rt'\n");
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		error_format("Error\nopen: error file\n");
	return (fd);
}

void	read_rt(int fd, t_scene *scene)
{
	char *str;

	str = ft_gnl(fd);
	while (str)
	{
		if (str[0] == 'A' && str[1] == ' ')
			ambient_lightning(scene, str);
		else if (str[0] == 'C' && str[1] == ' ')
			camera(scene, str);
		else if (str[0] == 'L' && str[1] == ' ')
			light(scene, str);
		else if (str[0] == 's' && str[1] == 'p' && str[2] == ' ')
			sphere(scene, str);
		else if (str[0] == 'p' && str[1] == 'l' && str[2] == ' ')
			plane(scene, str);
		else if (str[0] == 'c' && str[1] == 'y' && str[2] == ' ')
			cylinder(scene, str);
		else if (str[0] != '\n')
			exit_parse(scene);
		free(str);
		str = ft_gnl(fd);
	}
}

void	parse_rt(char *arg, t_scene *scene)
{
	int	fd;

	fd = open_file(arg);
	scene->fd = fd;
	read_rt(fd, scene);
	close(fd);
}
