/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:56:35 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/08/22 20:56:37 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pnt;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		pnt = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(pnt, del);
	}
}
