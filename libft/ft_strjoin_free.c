/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 22:14:48 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/19 22:15:18 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	l;
	size_t	j;
	size_t	s1_count;
	size_t	s2_count;
	char	*arr;

	if (!s1 && !s2)
		return (NULL);
	l = -1;
	j = 0;
	s1_count = ft_strlen(s1);
	s2_count = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (s1_count + s2_count + 1));
	if (!arr)
		return (NULL);
	while (++l < s1_count)
		arr[l] = s1[l];
	while (j < s2_count)
		arr[l++] = s2[j++];
	arr[l] = '\0';
	if (s1)
		free (s1);
	return (arr);
}
