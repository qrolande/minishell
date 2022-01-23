/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:37:06 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/23 16:23:54 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

// void	ft_ex_error(char *str)
// {
// 	write(2, "minishell: exit: ", 17);
// 	write(2, str, ft_strlen(str));
// 	write(2, ": numeric argument required\n", 29);
// 	g_ex_flag = 255;	
// }

unsigned long long	ft_atoi_long(char *str, int i)
{
	unsigned long long	res;
	
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}
