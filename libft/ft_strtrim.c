/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:51:19 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 16:51:20 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	beg;

	if (s1 == NULL)
		return (NULL);
	beg = 0;
	len = ft_strlen(s1);
	str = 0;
	if (s1 != 0 && set != 0)
	{
		while (ft_strchr(set, s1[beg]) && s1[beg] != '\0')
			beg++;
		while (ft_strchr(set, s1[len - 1]) && len > beg)
			len--;
		str = (char *)malloc(sizeof(char) * (len - beg + 1));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, &s1[beg], len - beg + 1);
	}
	return (str);
}
