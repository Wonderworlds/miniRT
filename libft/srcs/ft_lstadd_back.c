/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:06:09 by fmauguin          #+#    #+#             */
/*   Updated: 2021/12/18 16:35:06 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*index;

	if (!alst || !new)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		index = ft_lstlast(*alst);
		index->next = new;
	}
}
