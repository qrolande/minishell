/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:49:39 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:49:41 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numcheck(char *str, int res)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (n * res > 2147483647)
			return (-1);
		else if (n * res < -2147483648)
			return (0);
		else
			n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	long	nmbr;
	int		i;
	int		res;
	char	*s1;

	res = 1;
	i = 0;
	s1 = (char *) str;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			res = -1;
	nmbr = ft_numcheck(&s1[i], res);
	return ((int)(res * nmbr));
}
