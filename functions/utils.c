/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:37:06 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/30 01:40:33 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

static t_structenv	*ft_lstlast_env(t_structenv *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_env(t_structenv **lst, t_structenv *new)
{
	t_structenv	*temp;

	if (new == NULL)
		return ;
	else if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast_env(*lst);
		temp->next = new;
	}
}

void	error_output(char *str)
{
	ft_putstr_fd("minishell> export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}
