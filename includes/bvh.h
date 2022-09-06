/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:31:15 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/06 16:31:56 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "structs_utils.h"

//		bvh/bvh_construction.c
t_bvh			*build_node(t_list **vols, t_bvh **root,
					unsigned int begin, unsigned int end);

//		bvh/bvh_utils.c
t_bvh			*btree_create_node(t_box box, t_vol *vol);
void			btree_remove_infix(t_bvh **root, void (*applyf)(void *));

//		bvh/print_bvh.c
void			print_bvh(char *prefix, t_bvh *node, int is_left);

//		bvhbvh/sort_bvh.c
unsigned int	sort_vols(t_list **vols, const t_box *box,
					unsigned int begin, unsigned int end);

#endif