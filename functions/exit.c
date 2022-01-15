/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:02:51 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/15 18:58:42 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_sign(t_shell	*shell)
{
	
}

void	ft_exit(t_shell	*shell)
{
	int		i;
	int		sign;

	i = 0;
	if (shell->cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return ;
	}
	if (shell->cmd[1])
	{
		sign = find_sign(shell);
	}
	exit(EXIT_SUCCESS);
}