/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:37:06 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/30 07:45:22 by qrolande         ###   ########.fr       */
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

void	env_error_msg(t_shell *shell)
{
	printf("minishell> %s: %s\n", shell->cmd[0], \
				"No such file or directory");
	shell->error += 1;
	g_ex_flag = 1;
}
