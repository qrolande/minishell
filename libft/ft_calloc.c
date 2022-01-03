/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:49:45 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:49:46 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	res;

	res = count * size;
	str = (char *)malloc(sizeof(char) * res);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, res);
	return (str);
}
