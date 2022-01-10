/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:15:13 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 15:52:34 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	del_space(char *str, int i, int j)
{
	while (str[i])
	{
		if ((str[i] != ' ' && str[i + 1]) || str[i + 1] != ' ')
			j++;
		i++;
	}
	return (j);
}

char	*prepare_cmd(char *str)
{
	int		i;
	int		j;
	int		res;
	char	*tmp_str;

	i = 0;
	j = 0;
	res = del_space(str, i, j);
	tmp_str = (char *)malloc(res + 1);
	while (str[i])
	{
		if ((str[i] != ' ' && str[i + 1]) || str[i + 1] != ' ')
		{
			tmp_str[j] = str[i];
			j++;
		}
		i++;
	}
	tmp_str[j] = '\0';
	if (tmp_str[0] == ' ')
		tmp_str = ft_strdup(tmp_str + 1);
	free(str);
	return (tmp_str);
}
