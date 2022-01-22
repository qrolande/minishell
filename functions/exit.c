/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:02:51 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/22 18:34:01 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_args(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->cmd[i])
	{
		i++;
		if (i > 2)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			g_ex_flag = 1;
			return (1);
		}
	}
	if (i == 2)
		return (0);
}

void	ft_exit(t_shell	*shell)
{
	int i;
	int sign;

	sign = 1;
	write(2, "exit\n", 5);
	if (check_args(shell))
		return ;
	
	exit(g_ex_flag);
}