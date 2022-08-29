/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_construction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:01:38 by amahla            #+#    #+#             */
/*   Updated: 2022/08/29 15:42:09 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"

void	make_leaf(t_list *vols, t_bvh **root, unsigned int begin)
{
	t_vol	*vol;

	vols = ft_lst_at(vols, begin);
	vol = (t_vol *)(vols->content);
	(*root)->left = btree_create_node(vol->box, vol);
	if (vols->next)
	{
		vol = (t_vol *)(vols->next->content);
		(*root)->right = btree_create_node(vol->box, vol);
	}
}

t_bvh	*build_node(t_list *vols, t_bvh **root, unsigned int begin, unsigned int end)
{
	t_box			box;
	unsigned int	m;

	bounds_total(vols, &box, begin, end);
	*root = btree_create_node(box, NULL);
	if (end - begin <= 1)
	{
		make_leaf(vols, root, begin);
		return (*root);
	}
	m = sort_vols(&vols, &box, begin, end);
	ft_printf("\nm = %u\n", m);
	(*root)->left = build_node(vols, &(*root)->left, begin, m - 1);
	ft_printf("\nleft over\n");
	
	(*root)->right = build_node(vols, &(*root)->right, m, end);
	return (*root);
}
