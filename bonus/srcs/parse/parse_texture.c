/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:22:21 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 00:02:30 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs_utils.h"
#include "libft.h"
#include "mlx_data.h"

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

static size_t	set_t_xpm(t_scene *scene, char *str, t_xpm **xpm)
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

static size_t	set_disruption(t_scene *scene, char *str, t_disruption *ptr)
{
	const char	*ok[2] = {"checkerboard", "other"};
	size_t		i;

	i = 0;
//	if (*ptr != 0)
//		exit_parse(scene, NULL);
	while (ft_isalpha(str[i]))
		i++;
	if (!ft_strncmp(ok[0], str, i))
		*ptr = CHECKERBOARD;
	else if (!ft_strncmp(ok[1], str, i))
		*ptr = OTHER;
	else
		exit_parse(scene, NULL);
	while (str[i] == ' ')
		i++;
	return (i);
}

void	parse_vol_texture(t_scene *scene, t_vol *vol, char *str)
{
	const char		*tbd[4] = {"texture:", "bumpmap:", "disruption:",
		"specular:"};
	size_t			i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ':')
		{
			i++;
			if (!ft_strncmp(tbd[0], str, i))
				i += set_t_xpm(scene, &str[i],  &vol->tex);
			else if (!ft_strncmp(tbd[1], str, i))
				i += set_t_xpm(scene, &str[i], &vol->bump);
			else if (!ft_strncmp(tbd[2], str, i))
				i += set_disruption(scene, &str[i], &vol->disruption);
			else if (!ft_strncmp(tbd[3], str, i))
				i += set_specular(scene, str + i, &vol->spec);
			else
				exit_parse(scene, NULL);
			str += i;
			i = 0;
		}
		else
			i++;
	}
	if (i != 0)
		exit_parse(scene, NULL);
}

void	parse_pl_texture(t_scene *scene, t_plane *pl, char *str)
{
	const char		*tbd[4] = {"texture:", "bumpmap:", "disruption:",
		"specular:"};
	size_t			i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ':')
		{
			i++;
			if (!ft_strncmp(tbd[0], str, i))
				i += set_t_xpm(scene, &str[i], &pl->tex);
			else if (!ft_strncmp(tbd[1], str, i))
				i += set_t_xpm(scene, &str[i], &pl->bump);
			else if (!ft_strncmp(tbd[2], str, i))
				i += set_disruption(scene, &str[i], &pl->disruption);
			else if (!ft_strncmp(tbd[3], str, i))
				i += set_specular(scene, str + i, &pl->spec);
			else
				exit_parse(scene, NULL);
			str += i;
			i = 0;
		}
		else
			i++;
	}
	if (i != 0)
		exit_parse(scene, NULL);
}
