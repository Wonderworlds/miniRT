/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_lst_custom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:17:59 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:10:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "utils.h"

static void	swap_data(void **a, void **b);
static void	quicksort_lst(t_list **lst, size_t len, const t_pos *origin);

void	sort_list_custom(t_list **lst, const t_pos *origin,
			unsigned int begin, unsigned int end)
{
	size_t	size;
	t_list	*new_lst;

	if (!lst || !*lst)
		return ;
	new_lst = ft_lst_at(*lst, begin);
	size = end - begin;
	quicksort_lst(&new_lst, size, origin);
}

int	cmp_nearest_vol(const t_vol *left, const t_vol *right,
		const t_pos *origin)
{
	double	da;
	double	db;

	da = dist_ab(origin, &(left->box.center));
	db = dist_ab(origin, &(right->box.center));
	if (da < db)
		return (1);
	if (da > db)
		return (-1);
	return (0);
}

static void	quicksort_lst(t_list **lst, size_t len, const t_pos *origin)
{
	size_t		pivot;
	t_list		*vols[3];

	if (len <= 1)
		return ;
	pivot = 0;
	vols[0] = *lst;
	vols[1] = *lst;
	vols[2] = ft_lst_at(*lst, len - 1);
	while (vols[0] != vols[2]->next)
	{
		if (cmp_nearest_vol(vols[0]->content, vols[2]->content, origin) > 0)
		{
			swap_data(&vols[0]->content, &vols[1]->content);
			pivot++;
			vols[1] = vols[1]->next;
		}
		vols[0] = vols[0]->next;
	}
	swap_data(&vols[1]->content, &vols[2]->content);
	quicksort_lst(lst, pivot++, origin);
	vols[1] = vols[1]->next;
	quicksort_lst(&vols[1], len - pivot, origin);
}

static void	swap_data(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
