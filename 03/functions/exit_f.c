/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:44:57 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/15 19:02:39 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int hyphen_sign(t_node *data, int *hyph)
{
	int	n;

	n = 0;	
	if (data->cmd[1][0] == '-')
	{
		*hyph = *hyph *-1;
		n++;
	}
	if (data->cmd[1][0] == '+')
		n++;
	return (n);
}

static int	exit_digit(t_node *data, int *j, int ch)
{
	while (data->cmd[1][*j])
	{
		if (!ft_isdigit(data->cmd[1][*j]))
			ch = 1;
		*j = *j + 1;
	}
	return (ch);
}

static void exit_2_f(t_node *data, int j, int hyph)
{
	int	ch;
	unsigned long long	num;

	ch = 0;
	
	num = ft_atoi_long(data->cmd[1]);
	ch = exit_digit(data, &j, ch);
	if ((num > 9223372036854775807 && hyph == 1) 
		|| (num <= 9223372036854775807 && hyph == -1))
	{
		write(2, "minishell: exit: ", 17);
		write(2, data->cmd[1], ft_strlen(data->cmd[1]));
		write(2, ": numeric argument required\n", 29);
	}
	else
	{
		if (hyph)
			usleep(1);
		else	
			usleep(1);
	}
}

void	exit_f(t_node *data)
{
	int	i;
	int j;
	int hyph;

	i = 0;
	hyph = 1;
	write(2, "exit\n", 5);
	while (data->cmd[i])
		i++;
	if (i >= 3)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		// data->
		return ;
	}
	if (i == 2)
	{
		j = hyphen_sign(data, &hyph);
		exit_2_f(data, j, hyph);
	}
	exit(EXIT_SUCCESS);
}