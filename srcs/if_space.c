/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:41:24 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/05 17:24:36 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*del_space(char *str, t_shell *shell)
{
	char	*line1;
	char	*line2;

	line1 = ft_substr(str, 0, shell->i);
	while (str[shell->i] == ' ')
		shell->i++;
	line2 = ft_strdup(&str[shell->i - 1]);
	line1 = ft_strjoin(line1, line2);
	return (line1);
}

char	*if_space(char *str, t_shell *shell)
{
	while (str[shell->i] == ' ')
		shell->i++;
	str = ft_strdup(&str[shell->i]);
	shell->i = 0;
	while (str[shell->i])
	{
		if (str[shell->i] == '\'' || str[shell->i] == '\"')
		{
			shell->i++;
			while ((str[shell->i] != '\'' || str[shell->i] != '\"') \
				&& str[shell->i])
				shell->i++;
		}
		if (str[shell->i] == ' ' && str[shell->i + 1] == ' ')
				str = del_space(str, shell);
		shell->i++;
	}
	return (str);
}
