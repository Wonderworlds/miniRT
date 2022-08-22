/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:18:50 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/18 16:25:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*index;
	t_list	*prev;

	if (!lst || !del)
		return ;
	if (!*lst)
		return ;
	index = *lst;
	while (index)
	{
		prev = index;
		index = index->next;
		(*del)(prev->content);
		free(prev);
	}
	*lst = NULL;
}
