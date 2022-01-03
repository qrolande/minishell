/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:51:08 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:51:09 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned char	*a;
	size_t			i;

	a = (unsigned char *) s;
	i = 0;
	while (a[i] != '\0')
		i++;
	return (i);
}
