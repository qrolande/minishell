/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:02:51 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/23 21:44:25 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_ex_error(char *str)
{
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 29);
	g_ex_flag = 255;	
}

static int	first_pars(char *str, int i)
{
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_ex_error(str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		over_one(char *str)
{
	int 				i;
	int					sign;
	unsigned long long	res;

	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (first_pars(str, i))
		return (1);
	res = ft_atoi_long(str, i);
	if ((res > 9223372036854775807 && sign == 1) || (res > 9223372036854775808 && sign == -1))
	{
		ft_ex_error(str);
		return (1);
	}
	g_ex_flag = (int)((res * sign) % 256);
	return (0);
}

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
			return (0);
		}
	}
	return (i);
}

void	ft_exit(t_shell	*shell)
{
	int i;
	int res;

	write(2, "exit\n", 5);
	i = check_args(shell);
	if (!i)
		return ;
	if (i > 1)
	{
		if (over_one(shell->cmd[1]))
			return ;
	}
	exit(g_ex_flag);
}
