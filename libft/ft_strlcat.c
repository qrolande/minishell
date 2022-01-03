/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:51:03 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:51:04 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	o;
	int		len;

	i = 0;
	len = ft_strlen(dst) + ft_strlen(src);
	o = ft_strlen(dst);
	if (o > dstsize)
	{
		while (src[i] != '\0')
			i++;
		return (dstsize + i);
	}
	while (dstsize > 0 && o < dstsize - 1 && src[i] != '\0')
		dst[o++] = src[i++];
	dst[o] = '\0';
	return (len);
}
