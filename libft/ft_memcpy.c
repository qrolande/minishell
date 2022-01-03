/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:50:37 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:50:38 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*t;
	unsigned char	*y;
	int				i;

	t = (unsigned char *) dst;
	y = (unsigned char *) src;
	i = 0;
	if ((t == '\0') && (y == '\0'))
		return (dst);
	while (n != 0)
	{
		t[i] = y[i];
		i++;
		n--;
	}
	return (dst);
}
