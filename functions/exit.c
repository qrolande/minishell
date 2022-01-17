/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:02:51 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/16 17:37:08 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static long long	special_atoi(unsigned char	*str, int sign)
{
		
}

static int	find_sign(t_shell	*shell)
{
	if (shell->cmd[1][0] == '-')
		return (1);
	return (0);
}

void	ft_exit(t_shell	*shell)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	if (shell->cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return ;
	}
	if (shell->cmd[1])
	{
		sign = find_sign(shell);
		// printf("str = %s\n", shell->cmd[1]);
		while (shell->cmd[1][i + sign] >= 48 && shell->cmd[1][i + sign] <= 57)
		{
			// if ()
			i++;
		}
		res = special_atoi(shell->cmd[1], sign);
	}
	exit(EXIT_SUCCESS);
}