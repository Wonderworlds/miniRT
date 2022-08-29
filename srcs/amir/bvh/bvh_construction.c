/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_construction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:01:38 by amahla            #+#    #+#             */
/*   Updated: 2022/08/29 13:40:02 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"

void	make_leaf(t_list *vols, t_bvh *root, unsigned int begin, unsigned int end)
{
	t_vol	*vol;

	vols = ft_lst_at(vols, begin);
	vol = (t_vol *)(vols->content);
	root->left = btree_create_node(vol->box, vol);
	if (end - begin == 1)
	{
		vols = ft_lst_at(vols, end);
		vol = (t_vol *)(vols->content);
		root->right = btree_create_node(vol->box, vol);
	}
}

t_bvh	*build_node(t_list *vols, t_bvh *root, unsigned int begin, unsigned int end)
{
	t_box			box;
	unsigned int	m;
	t_bvh			*left;
	t_bvh			*right;

	bounds_total(vols, &box, begin, end);
	root = btree_create_node(box, NULL);
	if (end - begin <= 1)
	{
		make_leaf(vols, root, begin, end);
		return (root);
	}
	m = sort_vols(&vols, &box);
	left = build_node(vols, root->left, begin, m - 1);
	right = build_node(vols, root->right, m, end);
	return (root);
}
