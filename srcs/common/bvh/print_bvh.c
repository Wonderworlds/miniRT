/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bvh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:19:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 16:50:24 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "structs_utils.h"

static void	display_bvh_content(char *prefix, t_bvh *node, int is_left)
{
	const char	*e_type[] = {"NODE", "SPHERE", "PLANE", "CYLINDER"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[33m", "\x1b[36m", "\x1b[34m"};

	if (is_left)
		ft_printf("%s├──", prefix);
	else
		ft_printf("%s└──", prefix);
	if (!node)
		ft_printf("\x1b[31mNULL\x1b[0m\n");
	else if (node->vol == NULL)
	{
		ft_printf("%s%s\x1b[0m\n", e_colors[0], e_type[0]);
		// ft_printf("%s%s", e_colors[0], e_type[0]);
		// printf(" (%.1f, %.1f, %.1f)\x1b[0m\n", node->box.center.x,
		// 	node->box.center.y, node->box.center.z);
	}
	else
	{
		ft_printf("%s%s", e_colors[node->vol->type - SPHERE + 1],
			e_type[node->vol->type - SPHERE + 1]);
		printf(" (%.1f, %.1f, %.1f)\x1b[0m\n", node->vol->box.center.x,
			node->vol->box.center.y, node->vol->box.center.z);
	}
}

void	print_bvh(char *prefix, t_bvh *node, int is_left)
{
	char	*new_prefix;

	if (node)
	{
		display_bvh_content(prefix, node, is_left);
		if (is_left)
		{
			new_prefix = ft_strjoin(prefix, "│   ");
			print_bvh(new_prefix, node->left, 1);
			print_bvh(new_prefix, node->right, 0);
			if (!node->right && !node->vol)
				display_bvh_content(new_prefix, node->right, 0);
		}
		else
		{
			new_prefix = ft_strjoin(prefix, "    ");
			print_bvh(new_prefix, node->left, 1);
			print_bvh(new_prefix, node->right, 0);
			if (!node->right && !node->vol)
				display_bvh_content(new_prefix, node->right, 0);
		}
		free(new_prefix);
	}
}
