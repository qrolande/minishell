/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:39:29 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/07 20:12:42 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*gap(char *str, int *i)
{
	char	*str1;
	char	*str2;
	char	*str3;
	int		j;

	j = *i;
	while (str[*i])
	{
		if (str[*i] == '\'')
			break ;
		*i += 1;
	}
	str1 = ft_substr(str, 0, j);
	str2 = ft_substr(str, j + 1, *i - j - 1);
	str3 = ft_strdup(str + *i + 1);
	str1 = ft_strjoin(str1, str2);
	str1 = ft_strjoin(str1, str3);
	*i -= 1;
	free(str);
	return (str1);
}

