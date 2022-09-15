/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:16:47 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 00:46:47 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"

static void	malloc_xpm(char *str, t_xpm **xpm, t_scene *scene)
{
	*xpm = malloc(sizeof(t_xpm));
	if (!*xpm)
	{
		free(str);
		exit_parse(scene, "Error\nmalloc fail\n");
	}
	(*xpm)->file = str;
	(*xpm)->img = NULL;
	(*xpm)->addr = NULL;
}

size_t	set_t_xpm(t_scene *scene, char *str, t_xpm **xpm)
{
	size_t	i;
	char	*file;

	i = 0;
	if (*xpm)
		exit_parse(scene, NULL);
	while (str[i] && str[i] != ' ' && str[i] != '\n')
		i++;
	if (str[i] && str[i] != '\n' && str[i] != ' ')
		exit_parse(scene, NULL);
	file = ft_substr(str, 0, i);
	if (!file)
		exit_parse(scene, "Error\nmalloc fail\n");
	if (ft_strncmp(file + i - 4, ".xpm", 4) || access(file, F_OK))
	{
		free(file);
		exit_parse(scene, "Error\nIncorrect file\n");
	}
	malloc_xpm(file, xpm, scene);
	while (str[i] == ' ')
		i++;
	return (i);
}

static t_bool	specular_format(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',')
		return (false);
	i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		if (!ft_isdigit(str[++i]))
			return (false);
	while (ft_isdigit(str[i]))
		i++;
	return (true);
}

size_t	set_specular(t_scene *scene, char *str, t_spec *spec)
{
	size_t	i;

	i = 0;
	if (!specular_format(str))
		exit_parse(scene, NULL);
	if (ft_atoi_err(str, &spec->size) || spec->size < 0 || spec->size > 200)
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i++]))
		;
	if (ft_atof(str + i, &spec->intensity) || spec->intensity < 0
		|| spec->intensity > 2)
		exit_parse(scene, NULL);
	while (ft_isdigit(str[i]) || str[i] == '.' || str[i] == ' ')
		i++;
	return (i);
}
