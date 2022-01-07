/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:15:13 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/06 14:29:49 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*del_space(char *str, t_shell *shell)
{
	char	*line1;
	char	*line2;
	char	*line3;

	line1 = ft_substr(str, 0, shell->i);
	while (str[shell->i] == ' ')
		shell->i++;
	line2 = ft_strdup(&str[shell->i - 1]);
	line3 = ft_strjoin(line1, line2);
	free(line1);
	free(line2);
	return (line3);
}

char	*prepare_cmd(char *str, t_shell *shell)
{
	shell->i = 0;
	while (str[shell->i] == ' ')
		shell->i++;
	str = ft_strdup(&str[shell->i]);
	shell->i = 0;
	while (str[shell->i])
	{
		if (str[shell->i] == ' ' && str[shell->i + 1] == ' ')
				str = del_space(str, shell);
		shell->i++;
	}
	return (str);
}
