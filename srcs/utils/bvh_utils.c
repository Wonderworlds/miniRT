/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:03:50 by amahla            #+#    #+#             */
/*   Updated: 2022/08/29 15:54:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

t_bvh	*btree_create_node(t_box box, t_vol *vol)
{
	t_bvh	*node;

	node = malloc(sizeof(t_bvh));
	if (node)
	{
		box_cpy(&box, &node->box);
		node->vol = vol;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

void	btree_remove_infix(t_bvh **root, void (*applyf)(void *))
{
	if (!*root)
		return ;
	btree_remove_infix(&(*root)->left, applyf);
	btree_remove_infix(&(*root)->right, applyf);
	(*applyf)(*root);
	*root = NULL;
}
