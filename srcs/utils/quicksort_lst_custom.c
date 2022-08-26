/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_lst_custom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:17:59 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/25 19:56:29 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_utils.h"
#include "utils.h"

static void	swap_data(void **a, void **b);
static void	quicksort_lst(t_list **lst, size_t len, const t_pos *origin);

void	sort_list_custom(t_list **lst, const t_pos *origin)
{
	size_t	size;

	if (!lst || !*lst)
		return ;
	size = ft_lstsize(*lst);
	quicksort_lst(lst, size, origin);
}

int	cmp_nearest_vol(const t_vol *left, const t_vol *right,
		const t_pos *origin)
{
	if (dist_ab(origin, &(left->box.center))
		< dist_ab(origin, &(right->box.center)))
		return (1);
	return (0);
}

static void	quicksort_lst(t_list **lst, size_t len, const t_pos *origin)
{
	size_t		i;
	size_t		pivot;
	t_list		*new_start;

	if (len <= 1)
		return ;
	i = 0;
	pivot = 0;
	while (i < len)
	{
		if (cmp_nearest_vol((t_vol *)(ft_lst_at(*lst, i)->content),
			(t_vol *)(ft_lst_at(*lst, len - 1)->content), origin))
		{
			swap_data(&(ft_lst_at(*lst, i)->content),
				&(ft_lst_at(*lst, pivot)->content));
			pivot++;
		}
		i++;
	}
	swap_data(&(ft_lst_at(*lst, pivot)->content),
		&(ft_lst_at(*lst, len - 1)->content));
	quicksort_lst(lst, pivot++, origin);
	new_start = ft_lst_at(*lst, pivot);
	quicksort_lst(&new_start, len - pivot, origin);
}

static void	swap_data(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
