/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:50:05 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:56:29 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static char	*ft_printnbr(long nbr, char *res)
{
	if (nbr == 0)
		res[0] = '0';
	return (res);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*res;

	nbr = n;
	len = ft_length(nbr);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len--] = '\0';
	ft_printnbr(nbr, res);
	if (nbr < 0)
	{
		res[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		res[len--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (res);
}
