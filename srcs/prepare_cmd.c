/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:15:13 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/19 22:37:15 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*del_space(char *str, int *i)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(str, 0, *i);
	str2 = ft_strdup(str + *i + 1);
	str1 = ft_strjoin_free(str1, str2);
	free(str);
	free(str2);
	return (str1);
}

char	*prepare_cmd(char *str, int i)
{
	while (str[i] == ' ')
		str = del_space(str, &i);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while ((str[i] != '\'' || str[i] != '\"') && str[i])
				i++;
		}
		if (str[i + 1] && str[i] == ' ' && str[i + 1] == ' ')
		{
			str = del_space(str, &i);
			i = 0;
		}
		i++;
	}
	return (str);
}
