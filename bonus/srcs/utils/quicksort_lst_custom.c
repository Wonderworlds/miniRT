/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_lst_custom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:17:59 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/13 16:36:32 by fmauguin         ###   ########.fr       */
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
	float	da;
	float	db;

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
			(t_vol *)(ft_lst_at(*lst, len - 1)->content), origin) > 0)
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
