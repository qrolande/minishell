/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:50:14 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:50:15 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;

	if (lst != 0)
	{
		while (*lst != 0)
		{
			new = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = new;
		}
		*lst = NULL;
	}
}
